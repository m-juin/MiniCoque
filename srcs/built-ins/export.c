/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:22:49 by mjuin             #+#    #+#             */
/*   Updated: 2023/02/10 11:03:22 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static void	print_elem(t_env_var env, int fd)
{
	ft_printf_fd(fd, "declare -x %s", env.name);
	if (env.declared == 1)
	{
		if (env.value == NULL)
			ft_printf_fd(fd, "=\"\"\n");
		else
			ft_printf_fd(fd, "=\"%s\"\n", env.value);
	}
	else
		ft_printf_fd(fd, "\n");
}

static void	print_export(t_env_var *env, int fd)
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
				print_elem(*env, fd);
				cur_index++;
			}
			env = env->next;
		}
	}
}

static int	check_validity(char *path)
{
	size_t	pos;

	pos = 0;
	if (ft_isalpha(path[pos]) == 0 && path[pos] != '_')
		return (-1);
	while (path[pos] && (ft_isalnum(path[pos]) == 1 || path[pos] == '_'))
		pos++;
	if (path[pos] == '+' && path[pos + 1] == '=')
		return (1);
	else if (path[pos] == '=' || path[pos] == '\0')
		return (1);
	return (-1);
}

static int	handle_arg(t_env_var *env, char *arg)
{
	t_env_var	*tmp;

	if (check_validity(arg) == 1)
	{
		tmp = get_env(env, arg);
		if (tmp == NULL)
			ft_env_add_back(&env, create_env(arg));
		else
			replace_value(tmp, arg);
		return (0);
	}
	else
	{
		ft_printf_fd(2, "export: `%s\': not a valid identifier\n", arg);
		return (1);
	}
}

int	export(t_env_var *env, char **args)
{
	int			posx;
	int			ret;

	if (args[1] == NULL)
	{
		print_export(env, 1);
		g_exit_code = 0;
		return (0);
	}
	posx = 1;
	ret = 0;
	while (args[posx])
	{
		if (ret == 0)
			ret = handle_arg(env, args[posx]);
		else
			handle_arg(env, args[posx]);
		posx++;
	}
	g_exit_code = ret;
	return (ret);
}
