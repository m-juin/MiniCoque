/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:21:23 by mjuin             #+#    #+#             */
/*   Updated: 2023/02/10 11:41:08 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static void	remove_elem(t_env_var *lst, t_env_var *elem)
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

static int	get_error(char *path)
{
	size_t	pos;

	pos = 0;
	if (ft_isalpha(path[pos]) == 0 && path[pos] != '_')
	{
		ft_printf_fd(2, "export: `%s\': not a valid identifier\n", path);
		return (1);
	}
	while (path[pos] && (ft_isalnum(path[pos]) == 1 || path[pos] == '_'))
		pos++;
	if (path[pos] == '\0')
	{
		return (0);
	}
	ft_printf_fd(2, "export: `%s\': not a valid identifier\n", path);
	return (1);
}

static void	change_index(t_env_var *env, int index)
{
	while (env != NULL)
	{
		if (env->index > index)
			env->index--;
		env = env->next;
	}
}

int	unset(t_env_var *env, char **args)
{
	int			pos;
	t_env_var	*tmp;
	int			removedindex;
	int			ret;

	pos = 1;
	ret = 0;
	while (args[pos])
	{
		if (ret == 0)
			ret = get_error(args[pos]);
		else
			get_error(args[pos]);
		tmp = get_env(env, args[pos]);
		if (tmp != NULL)
		{
			removedindex = tmp->index;
			remove_elem(env, tmp);
			change_index(env, removedindex);
		}
		pos++;
	}
	last_exit(FALSE, ret);
	return (ret);
}
