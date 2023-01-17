/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:31:44 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/17 18:04:31 by gpasquet         ###   ########.fr       */
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

static void	word_extract(t_token *token, char *input, int i)
{
	int		start;

	start = i;
	while (input[i] && token_identifier(input[i])
		== token_identifier(input[i + 1]))
		i++;
	if (input[i])
		i++;
	token->token = ft_substr(input, start, i - start);
	if (!token->token)
	{
		token = NULL;
		return ;
	}
	token->token_type = token_identifier(token->token[0]);
}

static t_token	**token_join(char *input, t_env_var *env)
{
	t_token	**token_tab;
	int		i;
	int		token_nb;

	env = NULL;
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
		word_extract(token_tab[token_nb], &input[i], i);
		if (!token_tab[token_nb])
		{
			free_token(token_tab);
			return (NULL);
		}
		token_nb++;
		while (input[i] && token_identifier(input[i])
			== token_identifier(input[i + 1]))
			i++;
	}
	return (token_tab);
}

t_token	*lexer(char *input, t_env_var *env)
{
	t_token			**token_tab;
	int				i;

	token_tab = token_join(input, env);
	if (!token_tab)
		return (NULL);
	i = 0;
	while (token_tab[i])
	{
		printf("%s\n", token_tab[i]->token);
		i++;
	}
	free_token(token_tab);
	return (NULL);
}
