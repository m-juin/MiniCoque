/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_t_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:42:54 by mjuin             #+#    #+#             */
/*   Updated: 2023/02/09 17:13:40 by mjuin            ###   ########.fr       */
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
		if (path[pos - 1] == '+')
			new->name = ft_strndup(path, pos - 1);
		else
			new->name = ft_strndup(path, pos);
		new->value = ft_strndup(&path[pos + 1], -1);
	}
	return (new);
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
	else if (path[pos - 1] == '+' && path[pos] == '=')
		name = ft_strndup(path, pos - 1);
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
