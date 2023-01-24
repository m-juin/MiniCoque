/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:18:22 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/24 12:54:48 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static void	ft_read_tree(t_minicoque *data, t_btree *root, int fds[2])
{
	if (root == NULL)
		return ;
	while (root->type == PIPE)
	{
		child_cmd(fds, data, root);
		root = root->right;
	}
	last_exec(data, root, fds);
}

void init_tree_exec(t_minicoque *data, t_btree *root)
{
	t_btree *rooted;
	int		fds[2];

	rooted = root;
	fds[0] = 0;
	fds[1] = 1;
	if (root->type != PIPE)
		ft_execute(data, root, fds);
	else
	{
		ft_first_exec(data, root->left, fds);
		ft_read_tree(data, root->right, fds);
	}
}
