/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:22:49 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/18 14:37:38 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static void	print_elem(t_env_var env)
{
	ft_printf_fd(1, "declare -x %s", env.name);
	if (env.declared == 1)
	{
		if (env.value == NULL)
			ft_printf_fd(1, "=\"\"\n");
		else
			ft_printf_fd(1, "=\"%s\"\n", env.value);
	}
	else
		ft_printf_fd(1, "\n");
}

static void	print_export(t_env_var *env)
{
	int			cur_index;
	int			max_index;
	t_env_var	*tmp;

	tmp = env;
	max_index = get_env_size(env);
	cur_index = 0;
	while (cur_index < max_index - 1)
	{
		env = tmp;
		while (env != NULL)
		{
			if (env->index == cur_index)
			{
				print_elem(*env);
				cur_index++;
			}
			env = env->next;
		}
	}
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

static int	check_validity(char *path)
{
	size_t	pos;

	pos = 0;
	if (ft_isalpha(path[pos]) == 0)
		return (-1);
	while (path[pos] && ft_isalnum(path[pos]) == 1)
		pos++;
	if (path[pos] == '\0' || path[pos] == '=' )
		return (1);
	return (-1);
}

int	export(t_env_var *env, char **args)
{
	int			posx;
	t_env_var	*tmp;
	int			ret;

	if (args[1] == NULL)
	{
		print_export(env);
		return (0);
	}
	posx = 0;
	while (args[++posx])
	{
		if (check_validity(args[posx]) == 1)
		{
			tmp = get_env(env, args[posx]);
			if (tmp == NULL)
				ft_env_add_back(&env, create_env(args[posx]));
			else
				replace_value(tmp, args[posx]);
			ret = 0;
		}
		else
			ret = 1;
	}
	return (ret);
}
