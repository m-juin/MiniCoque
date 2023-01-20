/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:53:22 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/19 13:37:40 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

int	cd(t_env_var *env, char **args)
{
	int			ret;
	t_env_var	*tmp;

	if (args[1] == NULL || args[2] != NULL)
	{
		if (args[1] == NULL)
			ft_printf_fd(2, "cd need a parameter\n");
		else
			ft_printf_fd(2, "cd : too many arguments\n");
		last_exit(FALSE, 1);
		return (1);
	}
	ret = chdir(args[1]);
	if (ret == -1)
		ft_printf_fd(2, "cd: %s No such file or directory\n", args[1]);
	else
	{
		tmp = get_env(env, "PWD");
		if (tmp == NULL)
			return (ret);
		replace_value(get_env(env, "OLDPWD"), tmp->value);
		getcwd(tmp->value, PATH_MAX);
	}
	last_exit(FALSE, ret * -1);
	return (ret * -1);
}
