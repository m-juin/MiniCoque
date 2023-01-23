/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_management_functions.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:23:24 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/23 16:50:34 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static char	*simple_q(char *input, int *i)
{
	char	*s;

	(*i)++;
	while (input[*i] && (input[*i] != '\'' || input[*i] == '|'))
		(*i)++;
	if (!input[*i] || input[*i] == '|')
	{
		ft_printf_fd(2, "minicoque: syntax error nearunexpected `''\n");
	}
	s = ft_substr(input, 1, *i - 1);
	return (s);
}

char	*quotes_management(char *input, t_env_var *env, int *i)
{
	char	*s;

	(void)env;
	if (input[0] == '\'')
		s = simple_q(input, i);
	else
		return (NULL);
	//s = double_q(input, env);
	if (input[*i])
		(*i)++;
	return (s);
}
