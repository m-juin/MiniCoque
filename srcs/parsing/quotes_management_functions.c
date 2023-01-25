/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_management_functions.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:23:24 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/25 10:23:36 by gpasquet         ###   ########.fr       */
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

static char	*quoted_var(char *input, int *i, int *start, t_env_var *env)
{
	char		*s;
	int			start_param;
	t_env_var	*var;

	s = ft_substr(input, *start, *i - *start);
	(*i)++;
	start_param = *i;
	while (input[*i] && (typify(input[*i]) != BLANK && input[*i] != '|'
			&& input[*i] != '\"' && input[*i] != '\''
			&& input[*i] != '$'))
		(*i)++;
	var = get_env(env, ft_substr(input, start_param, *i - start_param));
	if (var)
		s = ft_strjoin(s, var->value);
	*start = *i;
	return (s);
}

static char	*double_q(char *input, int *i, t_env_var *env)
{
	char		*s;
	int			start;

	(*i)++;
	start = *i;
	while (input[*i] && (input[*i] != '\"' || input[*i] == '|'))
	{
		if (input[*i] == '$')
			s = quoted_var(input, i, &start, env);
		if (input[*i] != '\"')
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
	{
		s = ft_strjoin(s, ft_substr(input, start, *i - start));
	}
	return (s);
}

char	*quotes_management(char *input, t_env_var *env, int *i)
{
	char	*s;

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
