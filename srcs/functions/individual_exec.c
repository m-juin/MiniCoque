/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   individual_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:41:46 by mjuin             #+#    #+#             */
/*   Updated: 2023/02/09 09:36:18 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

void	ft_exec(t_btree *branch, t_minicoque *data)
{
	char *const	*env;
	int			ret;

	ret = 0;
	if (branch->left->tab_str[0] != NULL)
	{
		env = env_to_array(data->env_var);
		execve(branch->left->tab_str[0], branch->right->tab_str, env);
		d_tab_free((char **)env);
		ret = print_error(branch);
	}
	ft_close_fd(0, TRUE);
	ft_close_fd(1, TRUE);
	ft_global_free(data);
	exit(ret);
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
