/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:05:39 by mjuin             #+#    #+#             */
/*   Updated: 2023/02/08 13:34:26 by mjuin            ###   ########.fr       */
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
