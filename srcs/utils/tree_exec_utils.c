/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:18:22 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/24 12:54:18 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static void	ft_read_tree(t_minicoque *data, t_btree *root, int fds[2])
{
	/*int	pid;
	
	if (root == NULL)
		return ;
	while (root->type == PIPE)
	{
		pipe(fds[1]);
		pid = fork();
		if (pid == 0)
			child_cmd(fds, data, root);
		else
		{
			wait(NULL);
			close(fds[0][0]);
			close(fds[0][1]);
			fds[0][0] = fds[1][0];
			fds[0][1] = fds[1][1];
		}
		root = root->right;
	}
	pid = fork();
	if (pid == 0)
		last_exec(data, root, fds[0]);
	else
	{
		wait(NULL);
		close(fds[0][1]);
		close(fds[0][0]);
	}
		*/
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
	/*t_btree *tmp;
	int		fds[2][2];
	
	tmp = root;
		pipe(fds[0]);
		pipe(fds[1]);
	if (root->type == PIPE)
		ft_first_exec(data, root->left, fds);
	else
	{
		close(fds[0][0]);
		close(fds[1][0]);
		close(fds[0][1]);
		close(fds[1][1]);
		ft_execute(data, root);
	}
	close(fds[0][0]);
	close(fds[0][1]);
	fds[0][0] = fds[1][0];
	fds[0][1] = fds[1][1];
	if (root->type != PIPE)
	{
		close(fds[1][0]);
		close(fds[1][1]);
		return ;
	}
	ft_read_tree(data, root->right, fds);*/

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
