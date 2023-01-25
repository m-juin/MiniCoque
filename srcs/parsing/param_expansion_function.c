/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion_function.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:10:41 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/25 11:46:56 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

char	*doll_management(char *input, t_env_var *env)
{
	int			i;
	t_env_var	*var;

	i = 0;
	if (typify(input[i + 1]) != LITERAL)
		return (ft_strdup("$"));
	while (input[i])
	{
		if (typify(input[i]) != typify(input[i + 1]))
			break ;
		i++;
	}
	if (input[i])
		i++;
	var = get_env(env, ft_substr(input, 0, i));
	if (var)
		return (ft_strdup(var->value));
	else
		return (ft_strdup(""));
}
