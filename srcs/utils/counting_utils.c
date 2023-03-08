/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counting_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:43:29 by gpasquet          #+#    #+#             */
/*   Updated: 2023/03/08 10:34:17 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

void	counting_syntax_error(char input)
{
	char	*err_msg;

	err_msg = ft_strdup("minicoque: syntax error near unexpected token");
	if (input == '\0')
		ft_printf_fd(2, "%s `newline'\n", err_msg);
	else
		ft_printf_fd(2, "%s `%c'\n", err_msg, input);
	free(err_msg);
	g_exit_code = 2;
}

static int	redirect_count_loop(char *input, int *i)
{
	int		j;

	while (input[*i] && typify(input[*i]) != BLANK && typify(input[*i])
		!= REDIRECT && input[*i] != '|')
	{
		if (typify(input[*i]) == S_QUOTE || typify(input[*i]) == D_QUOTE)
		{
			j = *i;
			(*i)++;
			while (input[*i] && input[*i] != input[j])
				(*i)++;
		}
		if (!input[*i])
		{
			counting_syntax_error(input[*i]);
			return (-1);
		}
		(*i)++;
	}
	return (0);
}

int	redirect_count(char *input, int *i, int *nb)
{
	if (redirect_syntax_check(input, i) == -1)
		return (-1);
	(*nb)++;
	while (typify(input[*i]) == REDIRECT)
		(*i)++;
	while (typify(input[*i]) == BLANK)
		(*i)++;
	if (!input[*i] || input[*i] == '|' || typify(input[*i]) == REDIRECT)
	{
		counting_syntax_error(input[*i]);
		return (-1);
	}
	if (redirect_count_loop(input, i) == -1)
	{	
		g_exit_code = 2;
		return (-1);
	}
	return (0);
}

int	heredoc_count(t_token **token_tab)
{
	int	i;
	int	redir_nb;

	if (!token_tab)
		return (-1);
	redir_nb = 0;
	i = 0;
	while (token_tab[i])
	{
		if (token_tab[i]->token_type == HEREDOC)
			redir_nb++;
		i++;
	}
	return (redir_nb);
}
