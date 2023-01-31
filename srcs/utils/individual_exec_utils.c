/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   individual_exec_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:41:46 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/31 13:20:35 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static void deltmp(t_btree *root)
{
	if (root->tab_str[3][0] == 'D')
		unlink(root->tab_str[0]);
}

void	ft_single_exec(t_minicoque *data, t_btree *root, int fds[2])
{
	ft_execute(data, root, fds, root->type);
	fds[0] = ft_close_fd(fds[0], FALSE);
	fds[1] = ft_close_fd(fds[1], FALSE);
	deltmp(root);
}

void	last_exec(t_minicoque *data, t_btree *root, int fds[2])
{
	if (ft_isforkable(root->left->tab_str[0], root->right->tab_str[1]) == TRUE)
		ft_execute(data, root, fds, root->type);
	fds[0] = ft_close_fd(fds[0], FALSE);
	fds[1] = ft_close_fd(fds[1], FALSE);
	deltmp(root);
}

void	ft_first_exec(t_minicoque *data, t_btree *root, int fds[2])
{
	if (ft_isforkable(root->left->left->tab_str[0], root->left->right->tab_str[1]) != FALSE)
		ft_execute(data, root->left, fds, root->type);
	deltmp(root->left);
}

void	child_cmd(int fds[2], t_minicoque *data, t_btree *root)
{
	if (ft_isforkable(root->left->left->tab_str[0], root->left->right->tab_str[1]) != FALSE)
		ft_execute(data, root->left, fds, root->type);
	deltmp(root->left);
}
