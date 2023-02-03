/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion_function.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:10:41 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/03 10:19:02 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static char	*doll_expansion(char *input, t_env_var *env)
{
	int			i;
	t_env_var	*var;

	if (!input || !env)
		return (NULL);
	i = 0;
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

char	*doll_management(char *input, t_env_var *env)
{
	int			error_code;
	char		*expanded_param;

	if (!input || !env)
		return (NULL);
	expanded_param = NULL;
	if (input[0] == '?')
	{
		error_code = last_exit(TRUE, 0);
		return (ft_itoa(error_code));
	}
	if (typify(input[0]) != LITERAL)
		expanded_param = ft_strdup("$");
	else
		expanded_param = doll_expansion(input, env);
	return (expanded_param);
}
