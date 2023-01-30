/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:18:22 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/30 11:22:41 by mjuin            ###   ########.fr       */
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

void	ft_check_error(t_btree *root)
{
	if (root == NULL)
		return ;
	while (root->type == PIPE)
	{
		if (is_builtin(root->left->right->tab_str[0]) == 0)
		{
			if (access(root->left->left->tab_str[0], F_OK) != 0)
				ft_printf_fd(2, "%s: command not found\n",
					root->left->right->tab_str[0]);
			else if (access(root->left->left->tab_str[0], X_OK) != 0)
				ft_printf_fd(2, "MiniCoque: %s: Permission denied\n",
					root->left->left->tab_str[0]);
		}
		root = root->right;
	}
	if (is_builtin(root->right->tab_str[0]) == 0)
	{
		if (access(root->left->tab_str[0], F_OK) != 0)
			ft_printf_fd(2, "%s: command not found\n", root->right->tab_str[0]);
		else if (access(root->left->tab_str[0], X_OK) != 0)
			ft_printf_fd(2, "MiniCoque: %s: Permission denied\n",
				root->left->tab_str[0]);
	}
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
	{
		ft_first_exec(data, root, fds);
		ft_read_tree(data, root->right, fds);
	}
	ft_wait_pids(data->curprocess);
	ft_check_error(root);
	while (root->type == PIPE)
		root = root->right;
	free(data->curprocess);
}
