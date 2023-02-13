/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:37:39 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/13 10:48:53 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static	void	cmd_node_create(t_btree **parsed_tree, t_token **token_tab,
		t_env_var *env)
{
	t_btree	*cmd_node;

	if (!parsed_tree || !token_tab)
		return ;
	cmd_node = *parsed_tree;
	cmd_node->type = COMMAND;
	cmd_node->tab_str = redirtab_create(token_tab);
	if (!cmd_node->tab_str)
	{
		free_tree(cmd_node);
		return ;
	}
	cmd_node->right = insert_node(token_tab);
	if (cmd_node->right)
		cmd_node->left = insert_cmd_node(cmd_node->right->tab_str[0], env);
	else
	{
		free_tree(cmd_node);
		*parsed_tree = NULL;
	}
}

t_btree	*parsing(t_token **token_tab, t_env_var *env)
{
	t_btree	*parsed_tree;
	int		i;

	if (!token_tab || !env)
		return (NULL);
	parsed_tree = init_tree_node();
	if (!parsed_tree)
		return (NULL);
	i = 0;
	while (token_tab[i])
	{
		if (token_tab[i]->token_type == PIPE)
		{
			parsed_tree->type = PIPE;
			parsed_tree->left = parsing(sub_token_tab(token_tab, 0, i), env);
			parsed_tree->right = parsing(sub_token_tab(token_tab, i + 1,
						token_tab_len(token_tab, 0) - i), env);
			break ;
		}
		i++;
	}
	if (!token_tab[i])
		cmd_node_create(&parsed_tree, token_tab, env);
	token_tab = free_token(token_tab);
	return (parsed_tree);
}
