/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:53:22 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/18 13:00:07 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

int	cd(t_env_var *env, char **args)
{
	int			ret;
	t_env_var	*tmp;

	if (args[1] == NULL)
	{
		ft_printf_fd(2, "cd need a parameter");
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
	return (ret);
}