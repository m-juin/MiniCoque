/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   individual_exec_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:41:46 by mjuin             #+#    #+#             */
/*   Updated: 2023/02/08 12:07:55 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

void	ft_exec(t_btree *branch, t_minicoque *data)
{
	char *const	*env;

	env = env_to_array(data->env_var);
	if (branch->left->tab_str != NULL)
		execve(branch->left->tab_str[0], branch->right->tab_str, env);
	d_tab_free((char **)env);
	ft_close_fd(0, TRUE);
	ft_close_fd(1, TRUE);
	if (isfile(branch->left->tab_str[0]) == 0
		&& (branch->left->tab_str[0][0] == '/'
		|| ft_strncmp(branch->left->tab_str[0], "./", 2) == 0))
	{
		ft_printf_fd(2, "%s: Is a directory\n", branch->left->tab_str[0]);
		exit(126);
	}
	else if (branch->left->tab_str[0][0] == '/' ||
		ft_strncmp(branch->left->tab_str[0], "./", 2) == 0)
		ft_printf_fd(2, "%s: No such file or directory\n",
			branch->left->tab_str[0]);
	else
		ft_printf_fd(2, "%s: command not found\n", branch->left->tab_str[0]);
	ft_global_free(data);
	exit(127);
}

static void	deltmp(t_btree *root)
{
	if (root->tab_str[3][0] == 'D')
		unlink(root->tab_str[0]);
}

void	ft_single_exec(t_minicoque *data, t_btree *root, int fds[2])
{
	ft_solo_exec(data, root, fds, root->type);
	fds[0] = ft_close_fd(fds[0], FALSE);
	fds[1] = ft_close_fd(fds[1], FALSE);
	deltmp(root);
}

void	last_exec(t_minicoque *data, t_btree *root, int fds[2])
{
	ft_mult_execute(data, root, fds, root->type);
	fds[0] = ft_close_fd(fds[0], FALSE);
	fds[1] = ft_close_fd(fds[1], FALSE);
	deltmp(root);
}

void	child_cmd(int fds[2], t_minicoque *data, t_btree *root)
{
	ft_mult_execute(data, root->left, fds, root->type);
	deltmp(root->left);
}
