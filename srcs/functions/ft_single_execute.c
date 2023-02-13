/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_single_execute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:14:43 by mjuin             #+#    #+#             */
/*   Updated: 2023/02/13 14:49:30 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static int	solo_hfork(t_btree *root, int fds[2], t_minicoque *data, int type)
{
	int	fd;
	int	pid;

	if (root == NULL || data == NULL)
		return (-1);
	if (root->left->tab_str[0] != NULL)
		if (ft_isforkable(root->left->tab_str[0],
				root->right->tab_str[1]) == FALSE)
			return (1);
	fd = get_entry_fd(fds, root);
	set_exit_fd(root, type, fds, fd);
	signal(SIGINT, fsighandler);
	pid = fork();
	if (pid == 0)
	{
		ft_init_fork(fds, fd, data);
		return (2);
	}
	else
	{
		ft_handle_parent(pid, data, fd);
		return (-1);
	}
}

void	ft_solo_exec(t_minicoque *data, t_btree *root, int fds[2], int type)
{
	int	handled;
	int	exit_code;

	if (root == NULL || data == NULL)
		return ;
	handled = solo_hfork(root, fds, data, type);
	if (handled == -1)
		return ;
	choose_exec(data, root);
	if (handled == 2)
	{
		ft_close_fd(0, TRUE);
		ft_close_fd(1, TRUE);
		exit_code = g_exit_code;
		ft_global_free(data);
		exit(exit_code);
	}
}
