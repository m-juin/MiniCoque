/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_management_functions.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:23:24 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/24 13:03:16 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static char	*simple_q(char *input, int *i)
{
	char	*s;
	int		start;

	(*i)++;
	start = *i;
	while (input[*i] && (input[*i] != '\'' || input[*i] == '|'))
		(*i)++;
	if (!input[*i] || input[*i] == '|')
	{
		ft_printf_fd(2, "minicoque: syntax error near unexpected `''\n");
		return (NULL);
	}
	s = ft_substr(input, start, *i - start);
	return (s);
}

static char	*double_q(char *input, int *i, t_env_var *env)
{
	char	*s;
	t_env_var	*var;
	int		start;
	int		start_param;

	(*i)++;
	start = *i;
	while (input[*i] && (input[*i] != '\"' || input[*i] == '|'))
	{
		if (input[*i] == '$')
		{
			s = ft_substr(input, start, *i - start);
			(*i)++;
			start_param = *i;
			while (input[*i] && (typify(input[*i]) != BLANK && input[*i] != '|' && input[*i] == '\"' && input[*i] == '\''))
					(*i)++;
			var = get_env(env, ft_substr(input, start_param, *i - start_param - 1));
			if	(var)
			{
				s = ft_strjoin(s, var->value);
				free(var);
			}
			start = *i;
		}
		(*i)++;
	}	
	if ((!input[*i] || input[*i] == '|') && !s)
	{
		ft_printf_fd(2, "minicoque: syntax error near unexpected `''\n");
		return (NULL);
	}
	if (!s)
		s = ft_substr(input, start, *i - start);
	else
		s = ft_strjoin(s, ft_substr(input, start, *i - start));
	return (s);
}

char	*quotes_management(char *input, t_env_var *env, int *i)
{
	char	*s;

	(void)env;
	if (input[*i] == '\'')
		s = simple_q(input, i);
	else if (input[*i] == '\"')
		s = double_q(input, i, env);
	else
		return (NULL);
	if (input[*i])
		(*i)++;
	return (s);
}
