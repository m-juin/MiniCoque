/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:22:49 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/17 16:40:30 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static void print_export(t_env_var *env)
{
	int	cur_index;
	int	max_index;
	t_env_var *tmp;

	tmp = env;
	max_index = 0;
	while (env != NULL)
	{
		max_index++;
		env = env->next;
	}
	env = tmp;
	cur_index = 0;
	while (cur_index < max_index - 1)
	{
		env = tmp;
		while (env != NULL)
		{
			if (env->index == cur_index)
			{
				ft_printf("declare -x %s",env->name);
				if (env->declared == 1)
				{
					if (env->value == NULL)
						ft_printf("=\"\"\n");
					else
						ft_printf("=\"%s\"\n", env->value);
				}
				else
					ft_printf("\n");
				cur_index++;
			}
			env = env->next;
		}
	}
}

void replace_value(t_env_var *env, char *path)
{
	int	pos;

	pos = ft_strfindchr(path, '=');
	if (pos == -1)
		return ;
	if (env->value != NULL)
		free(env->value);
	env->value = ft_strndup(&path[pos + 1], -1);
	env->declared = 1;
}

int	export(t_env_var *env, char **args)
{
	int			posx;
	t_env_var	*tmp;
	
	if (args[1] == NULL)
	{
		print_export(env);
		return (0);
	}
	posx = 1;
	while (args[posx])
	{
		tmp = get_env(env, args[posx]);
		if (tmp == NULL)
			ft_env_add_back(&env, create_env(args[posx]));
		else
			replace_value(tmp, args[posx]);
		posx++;
	}
	return (1);
}