/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:36:00 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/31 16:41:44 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static void	ft_init_fork(int fds[2], int fd)
{
	if (fd == -1 || fds[1] == -1)
	{
		fd = ft_close_fd(fd, FALSE);
		exit (1);
	}
	secure_dup2(fd, 0);
	fds[0] = ft_close_fd(fds[0], FALSE);
	secure_dup2(fds[1], 1);
}

static void	ft_handle_parent(int pid, t_minicoque *data, int fd)
{
	int	pos;

	pos = 0;
	while (data->curprocess[pos] != -1)
		pos++;
	data->curprocess[pos] = pid;
	ft_close_fd(fd, FALSE);
}

static int	handlefork(t_btree *root, int fds[2], t_minicoque *data, int type)
{
	int	fd;
	int	pid;

	if (ft_isforkable(root->left->tab_str[0], root->right->tab_str[1]) == FALSE)
		return (1);
	else
	{
		fd = get_entry_fd(fds, root);
		set_exit_fd(root, type, fds, fd);
		pid = fork();
		if (pid == 0)
		{
			ft_init_fork(fds, fd);
			return (2);
		}
		else
		{
			ft_handle_parent(pid, data, fd);
			return (-1);
		}
	}
}

static void	choose_exec(t_minicoque *data, t_btree *root)
{
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
}

void	ft_execute(t_minicoque *data, t_btree *root, int fds[2], int type)
{
	int	handled;

	handled = handlefork(root, fds, data, type);
	if (handled == -1)
		return ;
	choose_exec(data, root);
	if (handled == 2)
	{
		ft_close_fd(0, TRUE);
		ft_close_fd(1, TRUE);
		exit(last_exit(TRUE, -1));
	}
}
