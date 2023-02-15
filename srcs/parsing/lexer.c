/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:31:44 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/15 17:07:34 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static void	dollar_token(t_token *token, char *input, t_env_var *env, int *i)
{
	char	*tmp;

	if (!token || !input)
		return ;
	(*i)++;
	if ((input[*i] == '\'' || input[*i] == '\"'))
		return ;
	else if (input[*i] == '\0' || input[*i] == '$')
		tmp = ft_strdup("$");
	else
		tmp = doll_management(&input[*i], env);
	get_to_var_end(input, i);
	if (!tmp)
		return ;
	if (tmp[0] == '\0')
	{
		free(tmp);
		return ;
	}
	replace_token_str(token, tmp);
}

static void	literal_token(t_token *token, char *input, int *i)
{
	char	*tmp;
	int		start;

	if (!token || !input)
		return ;
	start = *i;
	while (input[*i] && typify(input[*i]) == LITERAL)
		(*i)++;
	tmp = ft_substr(input, start, *i - start);
	replace_token_str(token, tmp);
}

static void	token_join_part2(t_token *token, char *input,
		t_env_var *env, int *i)
{
	int		start;
	char	*tmp;

	if (!token || !input)
		return ;
	start = *i;
	while (input[*i] && (typify(input[*i]) == LITERAL || input[*i] == '\''
			|| input[*i] == '\"' || input[*i] == '$'))
	{
		if (input[*i] == '\'' || input[*i] == '\"')
		{
			tmp = quotes_management(input, env, i);
			if (tmp)
				replace_token_str(token, tmp);
		}
		if (input[*i] == '$')
			dollar_token(token, input, env, i);
		if (typify(input[*i]) == LITERAL)
			literal_token(token, input, i);
		if (!token)
			free(token);
		if (token->token_type != REDIRECT && token->token_type != HEREDOC)
			token->token_type = LITERAL;
	}
}

static t_token	**token_join(char *input, t_env_var *env)
{
	t_token	**token_tab;
	int		i;
	int		nb;

	if (!input || !env)
		return (NULL);
	token_tab = init_tokentab(input);
	if (!token_tab)
		return (NULL);
	nb = 0;
	i = 0;
	while (input[i] && nb < token_empty_tab_len(token_tab))
	{
		while (typify(input[i]) == BLANK)
			i++;
		if (input[i] != '\0' && input[i] == '|')
			pipe_token(token_tab, &nb, input, &i);
		if (input[i] != '\0' && typify(input[i]) == REDIRECT)
			redirect_token(token_tab[nb], input, &i);
		token_join_part2(token_tab[nb], input, env, &i);
		if (!token_tab[nb])
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
