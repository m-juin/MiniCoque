/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:37:39 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/01 16:13:18 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static	void	cmd_node_create(t_btree *parsed_tree, t_token **token_tab,
		t_env_var *env)
{
	parsed_tree->type = COMMAND;
	parsed_tree->tab_str = redirtab_create(token_tab);
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
		cmd_node_create(parsed_tree, token_tab, env);
	free_token(token_tab);
	return (parsed_tree);
}
