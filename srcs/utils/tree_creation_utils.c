/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_creation_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:06:37 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/27 13:56:01 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

int	is_builtin(char	*str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	else if (ft_strcmp(str, "cd") == 0)
		return (1);
	else if (ft_strcmp(str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(str, "export") == 0)
		return (1);
	else if (ft_strcmp(str, "unset") == 0)
		return (1);
	else if (ft_strcmp(str, "env") == 0)
		return (1);
	else if (ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

t_btree	*init_tree_node(void)
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

t_btree	*insert_node(t_token **token_array)
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
	new_node->type = ARGS;
	return (new_node);
}

t_btree	*insert_cmd_node(t_token **array, t_env_var *env)
{
	t_btree	*new_node;
	int		i;

	new_node = init_tree_node();
	if (!new_node)
		return (NULL);
	new_node->tab_str = malloc(sizeof(char *) * 2);
	if (!new_node->tab_str)
	{
		free(new_node);
		return (NULL);
	}
	i = 0;
	while (array[i]->token_type == REDIRECT)
		i++;
	if (is_builtin(array[0]->str) == 1)
		new_node->tab_str[0] = ft_strdup(array[i]->str);
	else if (array[0]->str[0] == '/'
		|| (array[0]->str[0] == '.' && array[0]->str[1] == '/'))
		new_node->tab_str[0] = ft_strdup(array[i]->str);
	else
		new_node->tab_str[0] = get_cmds(array[i]->str, env_to_array(env));
	new_node->tab_str[1] = NULL;
	new_node->type = PATH;
	return (new_node);
}
