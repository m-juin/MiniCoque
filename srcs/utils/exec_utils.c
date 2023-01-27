/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:05:39 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/27 10:49:07 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static void	ft_exec(t_btree *branch, t_minicoque *data, int fds[2], int fd)
{
	int	pid;
	int	pos;

	pid = fork();
	if (pid == 0)
	{
		if (fd != 0 && fd != -1)
		{
			dup2(fd, 0);
			close(fds[0]);
		}
		if (fds[1] != 1 && fds[1] != -1)
		{
			dup2(fds[1], 1);
			close(fds[1]);
		}
		execve(branch->left->tab_str[0], branch->right->tab_str,
			env_to_array(data->env_var));
		exit (1);
	}
	else
	{
		pos = 0;
		while (data->curprocess[pos] != -1)
			pos++;
		data->curprocess[pos] = pid;
	}
	return ;
}

void	ft_execute(t_minicoque *data, t_btree *tree, int fds[2], int fd)
{
	if (tree->left->tab_str == NULL || tree->left->tab_str[0] == NULL)
		return ;
	else if (ft_strcmp(tree->left->tab_str[0], "exit") == 0)
		ft_exit(tree->right->tab_str, data);
	else if (ft_strcmp(tree->left->tab_str[0], "echo") == 0)
		echo(tree->right->tab_str, fds);
	else if (ft_strcmp(tree->left->tab_str[0], "env") == 0)
		env(data->env_var, tree->right->tab_str, fds);
	else if (ft_strcmp(tree->left->tab_str[0], "export") == 0)
		export(data->env_var, tree->right->tab_str, fds);
	else if (ft_strcmp(tree->left->tab_str[0], "unset") == 0)
		unset(data->env_var, tree->right->tab_str);
	else if (ft_strcmp(tree->left->tab_str[0], "pwd") == 0)
		pwd(fds);
	else if (ft_strcmp(tree->right->tab_str[0], "cd") == 0)
		cd(data->env_var, tree->right->tab_str);
	else
		ft_exec(tree, data, fds, fd);
}

void	ft_single_exec(t_minicoque *data, t_btree *tree, int fds[2])
{
	if (tree->tab_str != NULL && tree->tab_str[0] != NULL)
		fds[0] = open(tree->tab_str[0], O_RDONLY);
	if (fds[0] == -1)
		return ;
	if (tree->tab_str != NULL && tree->tab_str[1] != NULL)
	{
		if (tree->tab_str[2][0] == 'T')
			fds[1] = open(tree->tab_str[1], O_WRONLY, O_TRUNC);
		else
			fds[1] = open(tree->tab_str[1], O_WRONLY, O_APPEND);
	}
	if (fds[1] == -1)
	{
		if (fds[0] > 2)
			close(fds[0]);
		return ;
	}
	ft_execute(data, tree, fds, fds[0]);
	if (fds[1] > 2)
		close(fds[1]);
}

void	last_exec(t_minicoque *data, t_btree *tree, int fds[2], int fd)
{
	if (tree->tab_str != NULL && tree->tab_str[0] != NULL)
	{
		if (fd > 2)
			close(fd);
		fd = open(tree->tab_str[0], O_RDONLY);
	}
	if (fd == -1)
		return ;
	if (tree->tab_str != NULL && tree->tab_str[1] != NULL)
	{
		if (fds[1] > 2)
			close(fds[1]);
		if (tree->tab_str[2][0] == 'T')
			fds[1] = open(tree->tab_str[1], O_WRONLY, O_TRUNC);
		else
			fds[1] = open(tree->tab_str[1], O_WRONLY, O_APPEND);
	}
	else
		fds[1] = 1;
	if (fds[1] == -1)
	{
		if (fd > 2)
			close(fd);
		return ;
	}
	ft_execute(data, tree, fds, fd);
	if (fds[1] > 2)
		close(fds[1]);
	if (fds[0] > 2)
		close(fds[0]);
}

void	ft_first_exec(t_minicoque *data, t_btree *root, int fds[2])
{
	int	err;
	int	fd;

	err = 0;
	if (root->tab_str != NULL && root->tab_str[0] != NULL)
		fd = open(root->tab_str[0], O_RDONLY);
	else
		fd = fds[0];
	if (fd == -1)
		return ;
	if (root->tab_str != NULL && root->tab_str[1] != NULL)
	{
		if (root->tab_str[2][0] == 'T')
			fds[1] = open(root->tab_str[1], O_WRONLY, O_TRUNC);
		else
			fds[1] = open(root->tab_str[1], O_WRONLY, O_APPEND);
	}
	if (fds[1] == -1)
	{
		if (fd > 2)
			close(fd);
		return ;
	}
	if (root->tab_str == NULL || root->tab_str[1] == NULL)
		err = pipe(fds);
	if (err == -1)
		return ;
	if (ft_strcmp(root->left->left->tab_str[0], "export") != 0
		|| root->left->right->tab_str[1] == NULL)
		ft_execute(data, root->left, fds, fd);
}

void	child_cmd(int fds[2], t_minicoque *data, t_btree *tree, int fd)
{
	if (tree->tab_str != NULL && tree->tab_str[0] != NULL)
	{
		if (fd > 2)
			close(fd);
		fd = open(tree->tab_str[0], O_RDONLY);
	}
	if (fd == -1)
		return ;
	if (tree->tab_str != NULL && tree->tab_str[1] != NULL)
	{
		if (fds[1] > 2)
			close(fds[1]);
		if (tree->tab_str[2][0] == 'T')
			fds[1] = open(tree->tab_str[1], O_WRONLY, O_TRUNC);
		else
			fds[1] = open(tree->tab_str[1], O_WRONLY, O_APPEND);
	}
	if (fds[1] == -1)
	{
		if (fd > 2)
			close(fd);
		return ;
	}
	if (ft_strcmp(tree->left->tab_str[0], "export") != 0
		|| tree->right->tab_str[1] == NULL)
		ft_execute(data, tree, fds, fd);
}
