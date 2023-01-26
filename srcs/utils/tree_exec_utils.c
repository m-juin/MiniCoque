/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:18:22 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/26 09:52:43 by mjuin            ###   ########.fr       */
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

static int *ft_setcur(t_btree *root)
{
	int	pos;
	int	size;
	int	*curprocess;

	pos = 0;
	size = countcmd(root) + 1;
	curprocess = malloc(size * sizeof(int));
	if (curprocess == NULL)
		return (NULL);
	while(pos < size)
	{
		curprocess[pos] = -1;
		pos++;
	}
	return (curprocess);
}

void	ft_wait_pids(int *curprocess)
{
	int	pos;
	int exit_status;
	
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
		ft_execute(data, root, fds, 0);
	else
	{
		ft_first_exec(data, root->left, fds);
		ft_read_tree(data, root->right, fds);
	}
	ft_wait_pids(data->curprocess);
	ft_check_error(root);
	while(root->type == PIPE)
		root = root->right;
	if (is_builtin(root->right->tab_str[0]) == 0)
		last_exit(FALSE, errno);
	free(data->curprocess);
}
