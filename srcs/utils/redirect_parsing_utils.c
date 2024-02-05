/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parsing_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:50:36 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/15 16:58:45 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

int	redirect_syntax_check(char *input, int *i)
{
	char	*err_msg;

	err_msg = ft_strdup("minicoque: syntax error near unexpected token");
	if (typify(input[*i + 1]) == REDIRECT)
	{
		if (typify(input[*i + 2]) == REDIRECT)
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
	}
	free(err_msg);
	return (0);
}

int	redir_out_count( t_token **token_tab)
{
	int	i;
	int	redir_nb;

	redir_nb = 0;
	i = 0;
	while (token_tab[i])
	{
		if (token_tab[i]->str[0] == '>')
			redir_nb++;
		i++;
	}
	return (redir_nb);
}

char	*get_redir(char *str)
{
	char	*redir_path;
	int		i;
	int		start;

	i = 0;
	while (typify(str[i]) == REDIRECT)
		i++;
	while (typify(str[i]) == BLANK)
		i++;
	start = i;
	while (str[i])
		i++;
	redir_path = ft_substr(str, start, i - start);
	return (redir_path);
}

char	*get_redir_type(t_token **token_tab)
{
	char	*type;
	int		i;
	int		j;
	int		redir_nb;

	redir_nb = redir_out_count(token_tab);
	i = 0;
	j = 0;
	while (token_tab[i] && j < redir_nb)
	{
		if (token_tab[i]->str[0] == '>')
			j++;
		if (j == redir_nb)
		{
			if (token_tab[i]->str[1] == '>')
				type = ft_strdup("A");
			else
				type = ft_strdup("T");
		}	
		i++;
	}
	return (type);
}
