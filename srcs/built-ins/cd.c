/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:53:22 by mjuin             #+#    #+#             */
/*   Updated: 2023/02/10 11:00:59 by mjuin            ###   ########.fr       */
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

int	cd(t_env_var *env, char **args)
{
	int			ret;
	t_env_var	*tmp;

	if (error_handle(args) == FALSE)
		return (1);
	ret = chdir(args[1]);
	if (ret == -1)
		print_exec_error(args[1]);
	else
	{
		tmp = get_env(env, "PWD");
		if (tmp == NULL)
			return (ret);
		replace_value(get_env(env, "OLDPWD"), tmp->value);
		free(tmp->value);
		tmp->value = NULL;
		tmp->value = getcwd(tmp->value, PATH_MAX);
	}
	g_exit_code = ret * -1;
	return (ret * -1);
}
