/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:53:22 by mjuin             #+#    #+#             */
/*   Updated: 2023/02/20 11:24:33 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static void	print_exec_error(char *arg)
{
	if (errno == EACCES)
		ft_printf_fd(2, "cd: %s: Permission denied\n", arg);
	else if (errno == ENOTDIR)
		ft_printf_fd(2, "cd: %s: Not a directory\n", arg);
	else
		ft_printf_fd(2, "cd: %s: No such file or directory\n", arg);
}

static t_bool	error_handle(char **args)
{
	if (args[1] == NULL || args[2] != NULL)
	{
		if (args[1] == NULL)
			ft_printf_fd(2, "cd need a parameter\n");
		else
			ft_printf_fd(2, "cd : too many arguments\n");
		g_exit_code = 1;
		return (FALSE);
	}
	return (TRUE);
}

static void	set_new_value(t_env_var *env)
{
	t_env_var	*tmp;

	tmp = get_env(env, "PWD");
	if (tmp != NULL)
	{
		replace_value(get_env(env, "OLDPWD"), tmp->value);
		free(tmp->value);
		tmp->value = NULL;
		tmp->value = getcwd(tmp->value, PATH_MAX);
	}
	else
	{
		tmp = get_env(env, "OLDPWD");
		if (tmp == NULL)
			return ;
		tmp->declared = 0;
		s_free(tmp->value);
		tmp->value = NULL;
	}
}

int	cd(t_env_var *env, char **args)
{
	int			ret;

	if (error_handle(args) == FALSE)
		return (1);
	ret = chdir(args[1]);
	if (ret == -1)
		print_exec_error(args[1]);
	else
		set_new_value(env);
	g_exit_code = ret * -1;
	return (ret * -1);
}
