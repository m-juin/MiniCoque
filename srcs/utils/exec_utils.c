/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:05:39 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/31 11:49:58 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static void	secure_dup2(int source, int target)
{
	if (source != -1 && source != target)
	{
		dup2(source, target);
		ft_close_fd(source, FALSE);
	}
}

static t_bool	ft_isforkable(char *function, char *arg)
{
	if (ft_strcmp(function, "exit") == 0)
		return (FALSE);
	else if (ft_strcmp(function, "cd") == 0)
		return (FALSE);
	else if (ft_strcmp(function, "export") == 0 && arg != NULL)
		return (FALSE);
	else if (ft_strcmp(function, "unset") == 0)
		return (FALSE);
	return (TRUE);
}

static int ft_handlefork(t_btree *root, int fds[2], t_minicoque *data, int type)
{
	int	fd;
	int	pid;
	int	pos;

	if (ft_isforkable(root->left->tab_str[0], root->right->tab_str[1]) == FALSE)
		return (1);
	else
	{
		fd = get_entry_fd(fds, root);
		set_exit_fd(root, type, fds, fd);
		pid = fork();
		if (pid == 0)
		{
			secure_dup2(fd, 0);
			fds[0] = ft_close_fd(fds[0], FALSE);
			secure_dup2(fds[1], 1);
			return (2);
		}
		else
		{
			pos = 0;
			while (data->curprocess[pos] != -1)
				pos++;
			data->curprocess[pos] = pid;
			ft_close_fd(fd, FALSE);
			return (-1);
		}
	}
}

void	ft_exec(t_btree *branch, t_minicoque *data)
{
	
	execve(branch->left->tab_str[0], branch->right->tab_str,
	env_to_array(data->env_var));
}

void	ft_execute(t_minicoque *data, t_btree *root, int fds[2], int type)
{
	int handled;

	handled = ft_handlefork(root, fds, data, type);
	if (handled == -1)
		return ;
	if (ft_strcmp(root->left->tab_str[0], "exit") == 0)
		ft_exit(root->right->tab_str, data);
	else if (ft_strcmp(root->left->tab_str[0], "echo") == 0)
		echo(root->right->tab_str);
	else if (ft_strcmp(root->left->tab_str[0], "env") == 0)
		env(data->env_var, root->right->tab_str);
	else if (ft_strcmp(root->left->tab_str[0], "export") == 0)
		export(data->env_var, root->right->tab_str);
	else if (ft_strcmp(root->left->tab_str[0], "unset") == 0)
		unset(data->env_var, root->right->tab_str);
	else if (ft_strcmp(root->left->tab_str[0], "pwd") == 0)
		pwd();
	else if (ft_strcmp(root->right->tab_str[0], "cd") == 0)
		cd(data->env_var, root->right->tab_str);
	else
		ft_exec(root, data);
	if (handled == 2)
	{
		ft_close_fd(0, TRUE);
		ft_close_fd(1, TRUE);
		exit(1);
	}
}
