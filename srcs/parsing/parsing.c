/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:37:39 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/23 11:54:13 by gpasquet         ###   ########.fr       */
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

int	tab_len(t_token **tab)
{
	int	len;

	len = 0;
	while (tab[len])
		len++;
	return (len);
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
		sub_tab[i] = ft_calloc(1, sizeof(t_token));
		if (!sub_tab[i])
		{
			free_token(sub_tab);
			return (NULL);
		}
		sub_tab[i]->str = ft_strdup(token_tab[start + i]->str);
		if (!sub_tab[i]->str)
		{
			free_token(sub_tab);
			return (NULL);
		}
		sub_tab[i]->token_type = typify(sub_tab[i]->str[0]);
		i++;
	}
	sub_tab[i] = NULL;
	return (sub_tab);
}

t_btree	*parsing(t_token **token_tab, t_env_var *env)
{
	t_btree	*parsed_tree;
	int		i;

	parsed_tree = init_tree_node();
	i = 0;
	while (token_tab[i])
	{
		if (token_tab[i]->str[0] == '|')
		{
			parsed_tree->left = parsing(sub_token_tab(token_tab, 0, i), env);
			parsed_tree->right = parsing(sub_token_tab(token_tab, i + 1, tab_len(token_tab) - i), env);
			break ;
		}
		i++;
	}
	if (!token_tab[i])
	{
		parsed_tree->type = LITERAL;
		parsed_tree->right = insert_node(token_tab);
		parsed_tree->left = insert_cmd_node(token_tab, env);
	}
	return (parsed_tree);
}
