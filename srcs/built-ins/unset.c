/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:21:23 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/18 13:00:47 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

void	remove_elem(t_env_var *lst, t_env_var *elem)
{
	t_env_var	*tmp;

	while (lst->next != elem)
		lst = lst->next;
	tmp = lst->next->next;
	free(lst->next->name);
	free(lst->next->value);
	free(lst->next);
	lst->next = tmp;
}

int	unset(t_env_var *env, char **args)
{
	int			pos;
	t_env_var	*tmp;
	int			removedindex;

	pos = 1;
	while (args[pos])
	{
		tmp = get_env(env, args[pos]);
		if (tmp != NULL)
		{
			removedindex = tmp->index;
			remove_elem(env, tmp);
			tmp = env;
			while (env != NULL)
			{
				if (env->index > removedindex)
					env->index--;
				env = env->next;
			}
			env = tmp;
		}
		pos++;
	}
	return (0);
}
