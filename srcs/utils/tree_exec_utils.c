/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:18:22 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/25 11:31:24 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static void	ft_read_tree(t_minicoque *data, t_btree *root, int fds[2])
{
	int	fd;

	if (root == NULL)
		return ;
	while (root->type == PIPE)
	{
		fd = fds[0];
		close(fds[1]);
		pipe(fds);
		child_cmd(fds, data, root->left, fd);
		close(fd);
		root = root->right;
	}
	fd = fds[0];
	close(fds[1]);
	pipe(fds);
	last_exec(data, root, fds, fd);
	close(fd);
}

void	ft_check_error(t_btree *root)
{
	if (root == NULL)
		return ;
	while (root->type == PIPE)
	{
		if (is_builtin(root->left->right->tab_str[0]) == 0)
		{
			if (access(root->left->left->tab_str[0], F_OK) != 0)
				ft_printf_fd(2, "%s: command not found\n", root->left->right->tab_str[0]);
			else if (access(root->left->left->tab_str[0], X_OK) != 0)
				ft_printf_fd(2, "MiniCoque: %s: Permission denied\n", root->left->left->tab_str[0]);
		}
		root = root->right;
	}
	if (is_builtin(root->right->tab_str[0]) == 0)
	{
		if (access(root->left->tab_str[0], F_OK) != 0)
			ft_printf_fd(2, "%s: command not found\n", root->right->tab_str[0]);
		else if (access(root->left->tab_str[0], X_OK) != 0)
			ft_printf_fd(2, "MiniCoque: %s: Permission denied\n", root->left->tab_str[0]);
	}
}

void init_tree_exec(t_minicoque *data, t_btree *root)
{
	t_btree *rooted;
	int		fds[2];
	
	rooted = root;
	fds[0] = 0;
	fds[1] = 1;
	if (root->type != PIPE)
		ft_execute(data, root, fds, 0);
	else
	{
		ft_first_exec(data, root->left, fds);
		ft_read_tree(data, root->right, fds);
	}
	ft_check_error(rooted);
}