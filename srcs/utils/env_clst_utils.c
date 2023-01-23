/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_clst_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:39:45 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/23 15:12:54 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

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
