/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:18:22 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/23 15:21:55 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

void	ft_read_tree(t_minicoque *data, t_btree *root)
{
	while (root->type == PIPE)
	{
		ft_execute(data, root->left);
		root = root->right;
	}
	ft_execute(data, root);
}
