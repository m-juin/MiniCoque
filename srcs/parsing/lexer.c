/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:31:44 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/02 11:37:15 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static void	dollar_token(t_token *token, char *input, t_env_var *env, int *i)
{
	char	*tmp;

	while (input[*i] == '$')
	{
		(*i)++;
		tmp = doll_management(&input[*i], env);
		if (input[*i] == '?')
			(*i)++;
		else
		{
			while (input[*i] && typify(input[*i]) == LITERAL)
			(*i)++;
		}
		token->str = ft_strjoin(token->str, tmp);
		free(tmp);
	}
}

static void	literal_token(t_token *token, char *input, int *i)
{
	char	*tmp;
	int		start;

	start = *i;
	while (input[*i] && typify(input[*i]) == LITERAL)
		(*i)++;
	tmp = ft_substr(input, start, *i - start);
	token->str = ft_strjoin(token->str, tmp);
}

static void	token_join_part2(t_token *token, char *input,
			t_env_var *env, int *i)
{
	int		start;
	char	*tmp;

	start = *i;
	while (input[*i] && (typify(input[*i]) == LITERAL || input[*i] == '\''
			|| input[*i] == '\"' || input[*i] == '$'))
	{
		if (input[*i] == '\'' || input[*i] == '\"')
		{
			tmp = quotes_management(input, env, i);
			token->str = ft_strjoin(token->str, tmp);
			free(tmp);
		}
		if (input[*i] == '$')
			dollar_token(token, input, env, i);
		if (typify(input[*i]) == LITERAL)
			literal_token(token, input, i);
		if (!token || !token->str)
			free(token);
		if (token->token_type != REDIRECT)
			token->token_type = LITERAL;
	}
}

static t_token	**token_join(char *input, t_env_var *env)
{
	t_token	**token_tab;
	int		i;
	int		nb;

	token_tab = init_tokentab(input);
	if (!token_tab)
		return (NULL);
	nb = 0;
	i = 0;
	while (input[i])
	{
		while (typify(input[i]) == BLANK)
			i++;
		if (input[i] == '|')
			pipe_token(token_tab, &nb, input, &i);
		if (typify(input[i]) == REDIRECT)
			redirect_token(token_tab[nb], input, &i);
		token_join_part2(token_tab[nb], input, env, &i);
		if (token_tab[nb] && !token_tab[nb]->str)
			return (NULL);
		nb++;
	}
	return (token_tab);
}

t_token	**lexer(char *input, t_env_var *env)
{
	t_token	**token_tab;
	int		i;

	i = 0;
	if (!input)
		return (NULL);
	token_tab = token_join(input, env);
	if (!token_tab)
		return (NULL);
	return (token_tab);
}
