/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_management_functions.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:23:24 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/20 10:03:40 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static char	*simple_q(char *input, int *i)
{
	char	*s;
	int		start;

	if (!input)
		return (NULL);
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

static char	*double_q_part2(char *input, int *i, int *start, t_env_var *env)
{
	char	*s;

	if (!input || !env)
		return (NULL);
	s = "";
	s = ft_strjoin_f(s, ft_substr(input, *start, *i - *start), 2);
	s = ft_strjoin_f(s, quoted_var_management(input, i, start, env), 0);
	*start = *i;
	if ((input[*i] != '\"' && input[*i] != '$') || (input[*i] == '$'
			&& typify(input[*i + 1]) != LITERAL && input[*i + 1] != '$'))
		(*i)++;
	return (s);
}

static char	*double_q_loop(char *input, int *i, int *start, t_env_var *env)
{
	char		*s;

	s = NULL;
	while (input[*i] && input[*i] != '\"')
	{	
		if (input[*i] == '$')
		{
			if (s)
				s = ft_strjoin_f(s, double_q_part2(input, i, start, env), 0);
			else
				s = double_q_part2(input, i, start, env);
		}
		else
			(*i)++;
	}
	return (s);
}

static char	*double_q(char *input, int *i, t_env_var *env)
{
	char		*s;
	int			start;

	if (!input || !env)
		return (NULL);
	start = *i;
	s = double_q_loop(input, i, &start, env);
	if ((!input[*i] || input[*i] == '|') && !s)
	{
		ft_printf_fd(2, "minicoque: syntax error near unexpected `''\n");
		return (NULL);
	}
	s = finish_double_q(s, input, i, start);
	return (s);
}

char	*quotes_management(char *input, t_env_var *env, int *i)
{
	char	*s;

	if (!input || !env)
		return (NULL);
	if (input[*i] == '\'')
		s = simple_q(input, i);
	else if (input[*i] == '\"')
	{
		(*i)++;
		s = double_q(input, i, env);
	}
	else
		return (NULL);
	if (input[*i])
		(*i)++;
	return (s);
}
