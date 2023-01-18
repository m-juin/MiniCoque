/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 09:30:32 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/18 15:56:30 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

int	env(t_env_var *env_data, char **args)
{
	if (args[1] != NULL)
	{
		ft_putstr_fd("Too many argument for env\n", 2);
		last_exit(FALSE, 1);
	}
	if (env_data == NULL)
		last_exit(FALSE, 1);
	while (env_data != NULL)
	{
		if (env_data->declared == 1 && env_data->value != NULL)
			printf("%s=%s\n", env_data->name, env_data->value);
		else if (env_data->declared == 1)
			printf("%s=\n", env_data->name);
		env_data = env_data->next;
	}
	last_exit(FALSE, 0);
	return (1);
}
