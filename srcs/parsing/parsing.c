/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:37:39 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/23 10:53:33 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

void	free_tab(char **str_tab)
{
	int	i;

	i = 0;
	while (str_tab[i])
	{
		free(str_tab[i]);
		i++;
	}
	free(str_tab);
}

char	**tab_dup(char	**tab_str)
{
	char	**new_tab;
	int		len;
	int		i;

	len = strtab_len(tab_str);
	new_tab = malloc(sizeof(char *) * len + 1);
	if (!new_tab)
		return (NULL);
	i = 0;
	while (tab_str[i])
	{
		new_tab[i] = ft_strdup(tab_str[i]);
		if (!new_tab[i])
		{
			free_tab(new_tab);
			return (NULL);
		}
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

static t_btree	*init_tree_node(void)
{
	t_btree	*btree;

	btree = malloc(sizeof(t_btree));
	if (!btree)
		return (NULL);
	btree->tab_str = NULL;
	btree->left = NULL;
	btree->right = NULL;
	return (btree);
}

static t_btree	*insert_node(t_token **token_array)
{
	t_btree	*new_node;

	new_node = init_tree_node();
	if (!new_node)
		return (NULL);
	new_node->tab_str = token_to_array(token_array);
	if (!new_node->tab_str)
	{
		free(new_node);
		return (NULL);
	}
	return (new_node);
}

static	t_btree	*insert_cmd_node(t_token **array, t_env_var *env)
{
	t_btree	*new_node;

	new_node = init_tree_node();
	if (!new_node)
		return (NULL);
	new_node->tab_str = malloc(sizeof(char *) * 2);
	if (!new_node->tab_str)
	{
		free(new_node);
		return (NULL);
	}
	new_node->tab_str[0] = get_cmds(array[0]->str, env_to_array(env));
	new_node->tab_str[1] = NULL;
	return (new_node);
}

t_btree	*parsing(t_token **token_tab, t_env_var *env)
{
	t_btree	*parsed_tree;

	parsed_tree = init_tree_node();
	parsed_tree->type = LITERAL;
	parsed_tree->right = insert_node(token_tab);
	parsed_tree->left = insert_cmd_node(token_tab, env);
	return (parsed_tree);
}
