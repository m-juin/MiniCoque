/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:31:44 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/19 14:02:55 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

int	token_identifier(int c)
{
	if (c == ' ' || c == '	')
		return (BLANK);
	else if (c == '|')
		return (PIPE);
//	else if (c == '(' || c == ')')
//		return (PARENTHESIS);
	else if (c == '<' || c == '>')
		return (REDIRECT);
	return (LITERAL);
}

static int	token_count(char *input)
{
	int	token_nb;
	int	i;

	i = 0;
	token_nb = 0;
	while (input[i])
	{
		while (input[i] && token_identifier(input[i]) == BLANK)
			i++;
		if (input[i] == '|')
		{
			if (input[i + 1] == '|')
			{
				ft_printf_fd(2,
					"minicoque: syntax error near unexpected token `|''\n");
				return (-1);
			}
			token_nb++;
			i++;
		}
		else if (token_identifier(input[i]) == REDIRECT)
		{
			if (input[i] == input[i + 1] && input[i] == input[i + 2])
			{
				ft_printf_fd(2, "minicoque: syntax error near unexpected token `%c''\n", input[i]);
				return (-1);
			}
			token_nb++;
			i++;
		}
		else
		{
			token_nb++;
			while (input[i] && token_identifier(input[i]) == LITERAL)
				i++;
		}
	}
	return (token_nb);
}

static t_token	**token_join(char *input, t_env_var *env)
{
	t_token	**token_tab;
	int		i;
	int		start;
	int		token_nb;
	char	*tmp;

	token_nb = token_count(input);
	if (token_nb < 1)
		return (NULL);
	token_tab = init_tokentab(token_nb);
	if (!token_tab)
		return (NULL);
	token_nb = 0;
	i = 0;
	while (input[i])
	{
		while (input[i] && token_identifier(input[i]) != BLANK)
		{
			start = i;
			if (input[i] == '|')
			{
				if (token_tab[token_nb]->token[0] != '\0')
					token_nb++;
				token_tab[token_nb]->token = ft_strdup("|");
				if (token_identifier(input[i + 1]) == BLANK)
					i++;
				break ;
			}
			while (input[i] && token_identifier(input[i]) == LITERAL)
				i++;
			tmp = ft_substr(input, start, i - start);
			token_tab[token_nb]->token = ft_strjoin(token_tab[token_nb]->token,
					tmp);
			start = i;
	/*		if (input[i] == '\'' || input[i] == '\"')
			{
				tmp = quotes_management(&input[i], env);
				i += ft_strlen(tmp);
				token_tab[token_nb]->token = ft_strjoin(token_tab[token_nb]->token, tmp);
				free(tmp);
			}
	*/		if (input[i] == '$')
			{
				i++;
				tmp = doll_management(&input[i], env);
				while (input[i] && token_identifier(input[i]) == LITERAL)
					i++;
				token_tab[token_nb]->token
					= ft_strjoin(token_tab[token_nb]->token, tmp);
				free(tmp);
			}
			if (!token_tab[token_nb] || !token_tab[0]->token)
			{
				free_token(token_tab);
				return (NULL);
			}
		}
		token_tab[token_nb]->token_type
			= token_identifier(token_tab[token_nb]->token[0]);
		token_nb++;
		if (input[i])
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
