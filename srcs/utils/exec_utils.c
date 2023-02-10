/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:05:39 by mjuin             #+#    #+#             */
/*   Updated: 2023/02/10 11:44:13 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

int	*ft_setcur(t_btree *root)
{
	int	pos;
	int	size;
	int	*curprocess;

	pos = 0;
	if (root == NULL)
		return (NULL);
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

t_bool	ft_isforkable(char *function, char *arg)
{
	if (function == NULL)
		return (TRUE);
	if (ft_strcmp(function, "exit") == 0)
		return (FALSE);
	else if (ft_strcmp(function, "cd") == 0)
		return (FALSE);
	else if (ft_strcmp(function, "export") == 0 && arg != NULL)
		return (FALSE);
	else if (ft_strcmp(function, "unset") == 0)
		return (FALSE);
	return (TRUE);
}

int	print_error(t_btree *root)
{
	struct stat buf;
	int			ret;
	
	ret = stat(root->left->tab_str[0], &buf);
	if (ret == -1)
	{
		if (errno == EACCES)
			ft_printf_fd(2, "%s: Permission denied\n", root->left->tab_str[0]);
		else if (errno == ENOENT)
		{
			ft_printf_fd(2, "%s: No such file or directory\n",
				root->left->tab_str[0]);
		}
		return (126);
	}
	else
	{
		if (S_ISDIR(buf) == 0)
		{
			ft_printf_fd(2, "%s: Is a directory\n", root->left->tab_str[0]);
			return (126);
		}
	}
	/*if (isfile(branch->left->tab_str[0]) == 0
		&& (branch->left->tab_str[0][0] == '/'
		|| ft_strncmp(branch->left->tab_str[0], "./", 2) == 0))
	{
		ft_printf_fd(2, "%s: Is a directory\n", branch->left->tab_str[0]);
		return (126);
	}
	else if (branch->left->tab_str[0][0] == '/' ||
		ft_strncmp(branch->left->tab_str[0], "./", 2) == 0)
		ft_printf_fd(2, "%s: No such file or directory\n",
			branch->left->tab_str[0]);
	else
	{
		ft_printf_fd(2, "%s: command not found\n", branch->left->tab_str[0]);
	}
	return (127);*/
}
