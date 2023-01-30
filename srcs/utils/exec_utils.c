/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:05:39 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/30 10:46:37 by mjuin            ###   ########.fr       */
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

void	ft_exec(t_btree *branch, t_minicoque *data, int fds[2], int fd)
{
	int	pid;
	int	pos;

	pid = fork();
	if (pid == 0)
	{
		secure_dup2(fd, 0);
		secure_dup2(fds[1], 1);
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
