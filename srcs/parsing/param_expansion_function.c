/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion_function.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:10:41 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/06 14:58:50 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static char	*doll_expansion(char *input, t_env_var *env)
{
	int			i;
	t_env_var	*var;
	char		*tmp;

	if (!input || !env)
		return (NULL);
	i = -1;
	while (input[i++])
	{
		if (typify(input[i]) != typify(input[i + 1]))
			break ;
	}
	if (input[i])
		i++;
	tmp = ft_substr(input, 0, i);
	var = get_env(env, tmp);
	free(tmp);
	if (var)
	{
		tmp = ft_strdup(var->value);
		return (tmp);
	}
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
