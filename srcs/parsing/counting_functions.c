/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counting_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:54:10 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/08 10:44:29 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static int	d_quote_count(char *input, int *i, int *nb)
{
	if (!input)
		return (-1);
	(*i)++;
	while (input[*i] && input[*i] != '\"')
		(*i)++;
	if (!input[*i])
	{
		counting_syntax_error(input[*i]);
		return (-1);
	}
	if (typify(input[*i + 1]) != LITERAL && input[*i + 1] != '\''
		&& input[*i + 1] != '\"' && input[*i + 1] != '$')
		(*nb)++;
	(*i)++;
	return (0);
}

static int	s_quote_count(char *input, int *i, int *nb)
{
	if (!input)
		return (-1);
	(*i)++;
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	if (!input[*i])
	{
		counting_syntax_error(input[*i]);
		return (-1);
	}	
	if (!input[*i + 1]  || (typify(input[*i + 1]) != LITERAL
			&& input[*i + 1] != '\'' && input[*i + 1] != '\"'))
		(*nb)++;
	(*i)++;
	return (0);
}

static void	dollar_count(char *input, int *i, int *nb)
{
	if (!input)
		return ;
	(*i)++;
	while (input[*i] && typify(input[*i]) == LITERAL)
		(*i)++;
	if (typify(input[*i]) != DOLLAR)
		(*nb)++;
}

static int	token_count_part2(char *input, int *i, int *nb)
{
	if (!input)
		return (-1);
	if (input[*i] && typify(input[*i]) == REDIRECT)
	{
		if (redirect_count(input, i, nb) == -1)
			return (-1);
	}
	if (input[*i] == '\'')
		if (s_quote_count(input, i, nb) == -1)
			return (-1);
	if (input[*i] == '\"')
		if (d_quote_count(input, i, nb) == -1)
			return (-1);
	if (typify(input[*i]) == DOLLAR)
		dollar_count(input, i, nb);
	else if (typify(input[*i]) == LITERAL)
	{
		while (input[*i] && (typify(input[*i]) == LITERAL))
			(*i)++;
		if (typify(input[*i]) != DOLLAR && typify(input[*i]) != D_QUOTE
			&& typify(input[*i]) != S_QUOTE)
			(*nb)++;
	}
	return (0);
}

int	token_count(char *input)
{
	int		nb;
	int		i;

	if (!input)
		return (-1);
	i = 0;
	nb = 0;
	while (input[i])
	{
		while (input[i] && typify(input[i]) == BLANK)
			i++;
		if (input[i] && input[i] == '|')
		{
			if (pipe_count(input, &i, &nb) == -1)
				return (-1);
		}
		else if (input[i])
			if (token_count_part2(input, &i, &nb) == -1)
				return (-1);
	}
	return (nb);
}
