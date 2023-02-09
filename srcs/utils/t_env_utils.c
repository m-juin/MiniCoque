/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:00:50 by mjuin             #+#    #+#             */
/*   Updated: 2023/02/09 10:14:49 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

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

int	get_env_size(t_env_var *env)
{
	size_t	size;

	size = 0;
	while (env != NULL)
	{
		size++;
		env = env->next;
	}
	return (size);
}

char *const	*env_to_array(t_env_var *env)
{
	char	**array;
	size_t	size;
	size_t	pos;

	if (env == NULL)
		return (NULL);
	size = get_env_size(env);
	if (size == 0)
		return (NULL);
	array = malloc((size + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	pos = 0;
	while (env != NULL)
	{
		array[pos] = ft_str_mega_join("%s=%s", env->name, env->value);
		env = env->next;
		pos++;
	}
	array[pos] = NULL;
	return (array);
}
