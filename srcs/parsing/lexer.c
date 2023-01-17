/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:31:44 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/17 16:02:16 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static int	token_identifier(int c)
{
	if (c == ' ' || c == '	')
		return (BLANK);
	else if (c == '|')
		return (PIPE);
	else if (c == '\'')
		return (S_QUOTE);
	else if (c == '"')
		return (D_QUOTE);
	else if (c == '(' || c == ')')
		return (PARENTHESIS);
	else if (c == '<' || c == '>')
		return (BRACKET);
	else if (c == '$')
		return (DOLLAR);
	return (LITERAL);
}

static void	free_token(t_token **token_tab)
{
	int	i;

	i = 0;
	while (token_tab[i])
	{
		free(token_tab[i]->token);
		free(token_tab[i]);
		i++;
	}
	free(token_tab);
}

static int	token_count(char *input)
{
	int	token_nb;
	int	i;

	i = 0;
	token_nb = 0;
	while (input[i] == ' ' || input[i] == '	')
		i++;
	while (input[i])
	{
		while (input[i] == ' ' || input[i] == '	')
			i++;
		token_nb++;
		while (input[i] && token_identifier(input[i])
			== token_identifier(input[i + 1]))
			i++;
		if (input[i])
			i++;
	}
	return (token_nb);
}

static t_token	**init_tokentab(int token_nb)
{
	t_token	**token_tab;
	int		i;

	token_tab = ft_calloc(token_nb + 1, sizeof(t_token *));
	if (!token_tab)
		return (NULL);
	i = 0;
	while (i < token_nb)
	{
		token_tab[i] = ft_calloc(1, sizeof(t_token));
		if (!token_tab[i])
		{
			free_token(token_tab);
			return (NULL);
		}
		i++;
	}
	token_tab[i] = NULL;
	return (token_tab);
}

static t_token	**token_join(char *input)
{
	t_token	**token_tab;
	int		i;
	int		token_nb;
	int		start;

	token_nb = token_count(input);
	token_tab = init_tokentab(token_nb);
	if (!token_tab)
		return (NULL);
	token_nb = 0;
	i = 0;
	while (token_identifier(input[i]) == BLANK)
		i++;
	while (input[i])
	{
		while (token_identifier(input[i]) == BLANK)
			i++;
		start = i;
		while (input[i] && token_identifier(input[i])
			== token_identifier(input[i + 1]))
			i++;
		if (input[i])
			i++;
		token_tab[token_nb]->token = ft_substr(input, start, i - start);
		if (!token_tab[token_nb]->token)
		{
			free_token(token_tab);
			return (NULL);
		}
		token_tab[token_nb]->token_type
			= token_identifier(token_tab[token_nb]->token[0]);
		token_nb++;
	}
	return (token_tab);
}

t_token	*lexer(char *input)
{
	t_token			**token_tab;
	int				i;

	token_tab = token_join(input);
	if (!token_tab)
		return (NULL);
	i = 0;
	while (token_tab[i])
	{
		printf("%s est de type %d\n", token_tab[i]->token, token_tab[i]->token_type);
		i++;
	}
	free_token(token_tab);
	return (NULL);
}
