/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counting_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:54:10 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/26 16:54:27 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static int	redirect_count(char *input, int *i, int *nb)
{
	char	*err_msg;

	err_msg = ft_strdup("minicoque: syntax error nearunexpected token");
	if (redirect_syntax_check(input, i, err_msg) == -1)
		return (-1);
	(*nb)++;
	while (typify(input[*i]) == REDIRECT)
		(*i)++;
	while (typify(input[*i]) == BLANK)
		(*i)++;
	if (!input[*i] || input[*i] == '|' || typify(input[*i]) == REDIRECT)
	{
		if (input[*i] == '\0')
			ft_printf_fd(2, "%s `newline'\n", err_msg, input[*i]);
		else
			ft_printf_fd(2, "%s `%c'\n", err_msg, input[*i]);
		free(err_msg);
		return (-1);
	}
	while (input[*i] && typify(input[*i]) != BLANK && typify(input[*i])
		!= REDIRECT && input[*i] != '|')
			(*i)++;
	free(err_msg);
	return (0);
}

static void	d_quote_count(char *input, int *i, int *nb)
{
	(*i)++;
	while (input[*i] && input[*i] != '\"')
		(*i)++;
	if (typify(input[*i + 1]) != LITERAL && input[*i + 1] != '\''
		&& input[*i + 1] != '\"' && input[*i + 1] != '$')
		(*nb)++;
	if (!input[*i])
		return ;
	else
		(*i)++;
}

static void	dollar_count(char *input, int *i, int *nb)
{
	(*i)++;
	while (input[*i] && typify(input[*i]) == LITERAL)
		(*i)++;
	if (typify(input[*i]) != DOLLAR)
		(*nb)++;
}

static void	token_count_part2(char *input, int *i, int *nb)
{
	if (input[*i] == '\'')
	{
		(*i)++;
		while (input[*i] && input[*i] != '\'')
			(*i)++;
		if (typify(input[*i + 1]) != LITERAL && input[*i + 1] != '\''
			&& input[*i + 1] != '\"')
			(*nb)++;
		if (!input[*i])
			return ;
		else
			(*i)++;
	}
	if (input[*i] == '\"')
		d_quote_count(input, i, nb);
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
}

int	token_count(char *input)
{
	int		nb;
	int		i;

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
		else if (input[i] && typify(input[i]) == REDIRECT)
		{
			if (redirect_count(input, &i, &nb) == -1)
				return (-1);
		}
		else if (input[i])
			token_count_part2(input, &i, &nb);
	}
	return (nb);
}
