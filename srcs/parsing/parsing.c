/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:37:39 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/26 18:01:32 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>
#include <unistd.h>

static char	*redir_out(t_token **token_tab)
{
	int		redir_nb;
	int		i;
	int		j;
	char	*redir_path;

	redir_nb = redir_out_count(token_tab);
	redir_path = NULL;
	i = 0;
	j = 0;
	while (token_tab[i] && j < redir_nb)
	{
		if (token_tab[i]->str[0] == '>')
			j++;
		if (j == redir_nb)
		{	
			if (redir_path)
				free(redir_path);
			redir_path = get_redir(token_tab[i]->str);
			if (access(redir_path, F_OK) != 0)
				open(redir_path, O_CREAT, 0644);
		}
		i++;
	}
	return (redir_path);
}

static char	*redir_in(t_token **token_tab)
{
	int		redir_nb;
	int		i;
	int		j;
	char	*redir_path;

	redir_nb = redir_in_count(token_tab);
	redir_path = NULL;
	i = 0;
	j = 0;
	while (token_tab[i] && j < redir_nb)
	{
		if (token_tab[i]->str[0] == '<')
		{
			j++;
			redir_path = get_redir(token_tab[i]->str);
			if (access(redir_path, W_OK) != 0)
				return (redir_path);
		}
		i++;
	}
	return (redir_path);
}

static char	**redirtab_create(t_token **token_tab)
{
	char	**redir_tab;

	redir_tab = malloc(sizeof(char *) * 4);
	if (!redir_tab)
		return (NULL);
	redir_tab[0] = redir_in(token_tab);
	redir_tab[1] = redir_out(token_tab);
	if (redir_tab[1])
		redir_tab[2] = get_redir_type(token_tab);
	else
		redir_tab[2] = NULL;
	redir_tab[3] = NULL;
	return (redir_tab);
}

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
		if (token_tab[i]->str[0] == '|')
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
