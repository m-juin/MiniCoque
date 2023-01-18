/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:00:50 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/18 16:09:54 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

t_env_var	*create_env(char *path)
{
	int			pos;
	t_env_var	*new;

	new = malloc(sizeof(t_env_var));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->declared = 1;
	new->value = NULL;
	pos = ft_strfindchr(path, '=');
	if (pos == 0)
	{
		new->name = ft_strndup(path, -1);
		new->declared = -1;
	}
	else
	{
		new->name = ft_strndup(path, pos);
		new->value = ft_strndup(&path[pos + 1], -1);
	}
	return (new);
}

static int	get_new_index(t_env_var *lst, char *new_name)
{
	int	count;

	count = 0;
	if (ft_strcmp(new_name, "_") == 0)
		return (-1);
	while (lst != NULL)
	{
		if (ft_strcmp(lst->name, new_name) < 0
			&& ft_strcmp(lst->name, "_") != 0)
			count++;
		lst = lst->next;
	}
	return (count);
}

void	replace_value(t_env_var *env, char *path)
{
	int	pos;

	pos = ft_strfindchr(path, '=');
	if (pos == -1)
		return ;
	if (env->value != NULL)
		free(env->value);
	if (pos != 0)
		env->value = ft_strndup(&path[pos + 1], -1);
	else
		env->value = ft_strndup(&path[pos], -1);
	env->declared = 1;
}

t_env_var	*get_env(t_env_var *lst, char *path)
{
	int		pos;
	char	*name;

	pos = 0;
	name = NULL;
	while (path[pos] && path[pos] != '=')
		pos++;
	if (path[pos] == '\0')
		name = ft_strndup(path, -1);
	else
		name = ft_strndup(path, pos);
	while (lst != NULL)
	{
		if (ft_strcmp(lst->name, name) == 0)
			break ;
		lst = lst->next;
	}
	free(name);
	if (lst != NULL)
		return (lst);
	return (NULL);
}

void	ft_env_add_back(t_env_var **lst, t_env_var *new)
{
	t_env_var	*tmp;

	tmp = (*lst);
	if ((*lst) == NULL)
	{
		(*lst) = new;
		new->index = 0;
		return ;
	}
	new->index = get_new_index((*lst), new->name);
	while ((*lst)->next != NULL)
		(*lst) = (*lst)->next;
	(*lst)->next = new;
	(*lst) = tmp;
	while ((*lst) != NULL)
	{
		(*lst)->index = get_new_index(tmp, (*lst)->name);
		(*lst) = (*lst)->next;
	}
	(*lst) = tmp;
}
