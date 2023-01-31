/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:38:06 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/31 11:57:43 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static int	countcmd(t_btree *tree)
{
	int	count;

	count = 0;
	while (tree->type == PIPE)
	{
		count++;
		tree = tree->right;
	}
	count++;
	return (count);
}

int	*ft_setcur(t_btree *root)
{
	int	pos;
	int	size;
	int	*curprocess;

	pos = 0;
	size = countcmd(root) + 1;
	curprocess = malloc(size * sizeof(int));
	if (curprocess == NULL)
		return (NULL);
	while (pos < size)
	{
		curprocess[pos] = -1;
		pos++;
	}
	return (curprocess);
}

void	set_exit_fd(t_btree *curbranch, int type, int fds[2], int fd)
{
	ft_close_fd(fds[1], FALSE);
	if (curbranch->tab_str[1] != NULL)
	{
		if (fd != fds[0])
			fds[0] = ft_close_fd(fds[0], FALSE);
		pipe(fds);
		fds[1] = ft_close_fd(fds[1], FALSE);
		if (curbranch->tab_str[2][0] == 'T')
			fds[1] = open(curbranch->tab_str[1], O_WRONLY | O_TRUNC);
		else
			fds[1] = open(curbranch->tab_str[1], O_WRONLY | O_APPEND);
	}
	else if (type != PIPE)
		fds[1] = 1;
	else
		pipe(fds);
	return ;
}

int	get_entry_fd(int fds[2], t_btree *curbranch)
{
	int	new_fd;

	if (curbranch->tab_str[0] != NULL)
	{
		fds[0] = ft_close_fd(fds[0], FALSE);
		new_fd = open(curbranch->tab_str[0], O_RDONLY);
		if (new_fd == -1)
		{
			ft_printf_fd(2, "MiniCoque: %s: No such file or directory\n",
				curbranch->tab_str[0]);
			last_exit(FALSE, 1);
		}
	}
	else if (fds[0] >= 0)
		new_fd = fds[0];
	else
		new_fd = 0;
	return (new_fd);
}

int	ft_close_fd(int fd, t_bool force)
{
	if ((force == FALSE && fd < 3) || (force == TRUE && fd < 0))
		return (fd);
	close(fd);
	return (-1);
}
