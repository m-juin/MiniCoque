/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:57:31 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/07 10:13:08 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

int	typify(int c)
{
	if (c == ' ' || c == '	')
		return (BLANK);
	else if (c == '|')
		return (PIPE);
	else if (c == '$')
		return (DOLLAR);
	else if (c == '<' || c == '>')
		return (REDIRECT);
	else if (c == '\'')
		return (S_QUOTE);
	else if (c == '\"')
		return (D_QUOTE);
	else if (c == '\0')
		return (NUULL);
	return (LITERAL);
}

int	digit_str(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

t_token	*sub_token_create(t_token **token_tab, int pos)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = ft_strdup(token_tab[pos]->str);
	if (!token->str)
		return (NULL);
	token->token_type = token_tab[pos]->token_type;
	return (token);
}

t_token	**sub_token_tab(t_token **token_tab, int start, int len)
{
	t_token	**sub_tab;
	int		i;

	sub_tab = ft_calloc(len + 1, sizeof(t_token *));
	if (!sub_tab)
		return (NULL);
	i = 0;
	while (token_tab[start + i] && i < len)
	{
		sub_tab[i] = sub_token_create(token_tab, start + i);
		if (!sub_tab[i])
		{
			free_token(sub_tab);
			return (NULL);
		}
		i++;
	}
	sub_tab[i] = NULL;
	return (sub_tab);
}
