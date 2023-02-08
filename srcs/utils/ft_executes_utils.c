/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executes_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:16:02 by mjuin             #+#    #+#             */
/*   Updated: 2023/02/08 13:07:20 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

void	ft_init_fork(int fds[2], int fd, t_minicoque *data)
{
	if (fd == -1 || fds[1] == -1)
	{
		fds[0] = ft_close_fd(fds[0], FALSE);
		fd = ft_close_fd(fd, FALSE);
		fds[1] = ft_close_fd(fds[1], FALSE);
		ft_global_free(data);
		exit (1);
	}
	secure_dup2(fd, 0);
	fds[0] = ft_close_fd(fds[0], FALSE);
	secure_dup2(fds[1], 1);
}

void	ft_handle_parent(int pid, t_minicoque *data, int fd)
{
	int	pos;

	if (data == NULL)
		return ;
	pos = 0;
	while (data->curprocess[pos] != -1)
		pos++;
	data->curprocess[pos] = pid;
	ft_close_fd(fd, FALSE);
}

void	choose_exec(t_minicoque *data, t_btree *root)
{
	if (root == NULL || data == NULL)
		return ;
	if (root->left->tab_str[0] == NULL)
		ft_exec(root, data);
	else if (ft_strcmp(root->left->tab_str[0], "exit") == 0)
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
