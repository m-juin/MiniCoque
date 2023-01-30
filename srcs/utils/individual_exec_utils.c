/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   individual_exec_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:41:46 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/30 10:43:39 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

void	ft_single_exec(t_minicoque *data, t_btree *root, int fds[2])
{
	int	fd;

	fd = get_entry_fd(fds, root);
	set_exit_fd(root, root->type, fds);
	ft_execute(data, root, fds, fd);
	ft_close_fd(fd, FALSE);
	ft_close_fd(fds[1], FALSE);
}

void	last_exec(t_minicoque *data, t_btree *root, int fds[2])
{
	int	fd;

	fd = get_entry_fd(fds, root);
	set_exit_fd(root, root->type, fds);
	ft_execute(data, root, fds, fd);
	ft_close_fd(fd, FALSE);
}

void	ft_first_exec(t_minicoque *data, t_btree *root, int fds[2])
{
	int	fd;

	fd = get_entry_fd(fds, root->left);
	set_exit_fd(root->left, root->type, fds);
	if (fd == -1 || fds[1] == -1)
		return ;
	if (ft_strcmp(root->left->left->tab_str[0], "export") != 0
		|| root->left->right->tab_str[1] == NULL)
		ft_execute(data, root->left, fds, fd);
	ft_close_fd(fd, FALSE);
}

void	child_cmd(int fds[2], t_minicoque *data, t_btree *root)
{
	int	fd;

	fd = get_entry_fd(fds, root->left);
	set_exit_fd(root->left, root->type, fds);
	if (ft_strcmp(root->left->left->tab_str[0], "export") != 0
		|| root->left->right->tab_str[1] == NULL)
		ft_execute(data, root->left, fds, fd);
	ft_close_fd(fd, FALSE);
}
