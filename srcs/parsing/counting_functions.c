/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counting_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:54:10 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/20 15:16:38 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static int	pipe_count(char *input, int *i, int *nb)
{
	char	*err_msg;

	err_msg = ft_strdup("minicoque: syntax error nearunexpected token");
	if (input[*i + 1] == '|')
	{
		ft_printf_fd(2, "%s `|'\n", err_msg);
		free(err_msg);
		return (-1);
	}
	(*nb)++;
	(*i)++;
	free(err_msg);
	return (0);
}

static int	redirect_count(char *input, int *i, int *nb)
{
	char	*err_msg;

	err_msg = ft_strdup("minicoque: syntax error nearunexpected token");
	if (input[*i] == input[*i + 1] && input[*i] == input[*i + 2])
	{
		ft_printf_fd(2, "%s `%c'\n", err_msg, input[*i]);
		free(err_msg);
		return (-1);
	}
	if (input[*i] == '>' && input[*i + 1] == '<')
	{
		ft_printf_fd(2, "%s`%c'\n", err_msg, input[*i]);
		free(err_msg);
		return (-1);
	}
	(*nb)++;
	if ((input[*i] == '<' && input[*i + 1] == '>')
		|| input[*i] == input[*i + 1])
		(*i)++;
	(*i)++;
	free(err_msg);
	return (0);
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
	if (typify(input[*i]) == DOLLAR)
		dollar_count(input, i, nb);
	else if (typify(input[*i]) == LITERAL)
	{
		while (input[*i] && (typify(input[*i]) == LITERAL || typify(input[*i])
				== D_QUOTE || typify(input[*i]) == D_QUOTE))
			(*i)++;
		if (typify(input[*i]) != DOLLAR)
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
		if (input[i] == '|')
		{
			if (pipe_count(input, &i, &nb) == -1)
				return (-1);
		}
		else if (typify(input[i]) == REDIRECT)
		{
			if (redirect_count(input, &i, &nb) == -1)
				return (-1);
		}
		else
			token_count_part2(input, &i, &nb);
	}
	return (nb);
}
