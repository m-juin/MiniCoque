/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:18:22 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/31 16:30:41 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

int	countcmd(t_btree *tree)
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

static void	ft_wait_pids(int *curprocess)
{
	int	pos;
	int	exit_status;

	pos = 0;
	exit_status = 0;
	while (curprocess[pos] != -1)
	{
		waitpid(curprocess[pos], &exit_status, 0);
		if (WIFEXITED(exit_status))
			last_exit(FALSE, WEXITSTATUS(exit_status));
		pos++;
	}
}

void	init_tree_exec(t_minicoque *data, t_btree *root)
{
	int		fds[2];

	data->curprocess = ft_setcur(root);
	if (data->curprocess == NULL)
		return ;
	errno = 0;
	fds[0] = 0;
	fds[1] = 1;
	if (root->type != PIPE)
		ft_single_exec(data, root, fds);
	else
		ft_read_tree(data, root, fds);
	ft_wait_pids(data->curprocess);
	while (root->type == PIPE)
		root = root->right;
	free(data->curprocess);
}
