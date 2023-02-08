/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:38:54 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/08 11:39:50 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

void	replace_token_str(t_token *token, char *tmp)
{
	if (token->str)
		token->str = ft_strjoin_f(token->str, tmp, 0);
	else
		token->str = tmp;
}

void	pipe_token(t_token **token_tab, int *nb, char *input, int *i)
{
	if (!token_tab || !input)
		return ;
	free(token_tab[*nb]->str);
	token_tab[*nb]->str = ft_strdup("|");
	token_tab[*nb]->token_type = PIPE;
	(*nb)++;
	while (typify(input[*i]) == BLANK || input[*i] == '|')
		(*i)++;
}

void	redirect_token(t_token *token, char *input, int *i)
{
	int	start;

	start = *i;
	while (typify(input[*i]) == REDIRECT)
		(*i)++;
	while (typify(input[*i]) == BLANK)
		(*i)++;
	free(token->str);
	token->str = ft_substr(input, start, *i - start);
	token->token_type = REDIRECT;
}
