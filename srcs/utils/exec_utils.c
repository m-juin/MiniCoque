/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:05:39 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/30 10:29:05 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

int	ft_close_fd(int fd, t_bool force)
{
	if ((force == FALSE && fd < 3) || (force == TRUE && fd < 0))
		return (fd);
	close(fd);
	return (-1);
}

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
			ft_close_fd(fd, FALSE);
		}
		if (fds[1] != 1 && fds[1] != -1)
		{
			dup2(fds[1], 1);
			ft_close_fd(fds[1], FALSE);
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

void	ft_execute(t_minicoque *data, t_btree *root, int fds[2], int fd)
{
	if (root->left->tab_str == NULL || root->left->tab_str[0] == NULL)
		return ;
	else if (ft_strcmp(root->left->tab_str[0], "exit") == 0)
		ft_exit(root->right->tab_str, data);
	else if (ft_strcmp(root->left->tab_str[0], "echo") == 0)
		echo(root->right->tab_str, fds);
	else if (ft_strcmp(root->left->tab_str[0], "env") == 0)
		env(data->env_var, root->right->tab_str, fds);
	else if (ft_strcmp(root->left->tab_str[0], "export") == 0)
		export(data->env_var, root->right->tab_str, fds);
	else if (ft_strcmp(root->left->tab_str[0], "unset") == 0)
		unset(data->env_var, root->right->tab_str);
	else if (ft_strcmp(root->left->tab_str[0], "pwd") == 0)
		pwd(fds);
	else if (ft_strcmp(root->right->tab_str[0], "cd") == 0)
		cd(data->env_var, root->right->tab_str);
	else
		ft_exec(root, data, fds, fd);
}

void	set_exit_fd(t_btree *curbranch, int type, int fds[2])
{
	ft_close_fd(fds[1], FALSE);
	if (curbranch->tab_str[1] != NULL)
	{
		ft_close_fd(fds[0], FALSE);
		pipe(fds);
		ft_close_fd(fds[1], FALSE);
		if (curbranch->tab_str[2][0] == 'T')
			fds[1] = open(curbranch->tab_str[1], O_WRONLY, O_TRUNC);
		else
			fds[1] = open(curbranch->tab_str[1], O_WRONLY, O_APPEND);
	}
	else if (type != PIPE)
		fds[1] = 1;
	else
		pipe(fds);
	return ;
}

int	get_entry_fd(int fds[2], t_btree *curbranch)
{
	int	new_fd;

	if (curbranch->tab_str[0] != NULL)
	{
		ft_close_fd(fds[0], FALSE);
		new_fd = open(curbranch->tab_str[0], O_RDONLY);
	}
	else if (fds[0] >= 0)
		new_fd = fds[0];
	else
		new_fd = 0;
	return (new_fd);
}

void	ft_single_exec(t_minicoque *data, t_btree *root, int fds[2])
{
	int	fd;

	fd = get_entry_fd(fds, root);
	set_exit_fd(root, root->type, fds);
	ft_execute(data, root, fds, fd);
	ft_close_fd(fd, FALSE);
	ft_close_fd(fds[1], FALSE);
}

void	last_exec(t_minicoque *data, t_btree *root, int fds[2])
{
	int	fd;

	fd = get_entry_fd(fds, root);
	set_exit_fd(root, root->type, fds);
	ft_execute(data, root, fds, fd);
	ft_close_fd(fd, FALSE);
}

void	ft_first_exec(t_minicoque *data, t_btree *root, int fds[2])
{
	int	fd;

	fd = get_entry_fd(fds, root->left);
	set_exit_fd(root->left, root->type, fds);
	if (fd == -1 || fds[1] == -1)
		return ;
	if (ft_strcmp(root->left->left->tab_str[0], "export") != 0
		|| root->left->right->tab_str[1] == NULL)
		ft_execute(data, root->left, fds, fd);
	ft_close_fd(fd, FALSE);
}

void	child_cmd(int fds[2], t_minicoque *data, t_btree *root)
{
	int	fd;

	fd = get_entry_fd(fds, root->left);
	set_exit_fd(root->left, root->type, fds);
	if (ft_strcmp(root->left->left->tab_str[0], "export") != 0
		|| root->left->right->tab_str[1] == NULL)
		ft_execute(data, root->left, fds, fd);
	ft_close_fd(fd, FALSE);
}
