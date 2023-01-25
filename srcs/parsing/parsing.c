/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:37:39 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/25 11:24:26 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static t_token	*sub_token_create(t_token **token_tab, int pos)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = ft_strdup(token_tab[pos]->str);
	if (!token->str)
		return (NULL);
	token->token_type = typify(token->str[0]);
	return (token);
}

static t_token	**sub_token_tab(t_token **token_tab, int start, int len)
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

static	void	cmd_node_create(t_btree *parsed_tree, t_token **token_tab,
		t_env_var *env)
{
		parsed_tree->type = COMMAND;
		parsed_tree->right = insert_node(token_tab);
		parsed_tree->left = insert_cmd_node(token_tab, env);
}

t_btree	*parsing(t_token **token_tab, t_env_var *env)
{
	t_btree	*parsed_tree;
	int		i;

	if (!token_tab)
		return (NULL);
	parsed_tree = init_tree_node();
	i = 0;
	while (token_tab[i])
	{
		if (token_tab[i]->str[0] == '|')
		{
			parsed_tree->type = PIPE;
			parsed_tree->left = parsing(sub_token_tab(token_tab, 0, i), env);
			parsed_tree->right = parsing(sub_token_tab(token_tab, i + 1,
						token_tab_len(token_tab) - i), env);
			break ;
		}
		i++;
	}
	if (!token_tab[i])
		cmd_node_create(parsed_tree, token_tab, env);
	return (parsed_tree);
}
