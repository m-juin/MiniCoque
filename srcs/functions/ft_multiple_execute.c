/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multiple_execute.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:36:00 by mjuin             #+#    #+#             */
/*   Updated: 2023/02/13 14:44:42 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static int	mult_hfork(t_btree *root, int fds[2], t_minicoque *data, int type)
{
	int	fd;
	int	pid;

	if (root == NULL || data == NULL)
		return (-1);
	else
	{
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
}

void	ft_mult_execute(t_minicoque *data, t_btree *root, int fds[2], int type)
{
	int	handled;
	int	exit_code;

	if (root == NULL || data == NULL)
		return ;
	handled = mult_hfork(root, fds, data, type);
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
