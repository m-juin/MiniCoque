/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:37:39 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/26 16:05:03 by gpasquet         ###   ########.fr       */
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

static char	*get_redir(char *str)
{
	char	*redir_path;
	int		i;
	int		start;

	i = 0;
	while (typify(str[i]) == REDIRECT)
		i++;
	while (typify(str[i]) == BLANK)
		i++;
	start = i;
	while (str[i])
		i++;
	redir_path = ft_substr(str, start, i - start);
	return (redir_path);
}

static char	*redir_out(t_token **token_tab)
{
	int		redir_nb;
	int		i;
	int		j;
	char	*redir_path;

	i = 0;
	redir_nb = 0;
	redir_path = NULL;
	while (token_tab[i])
	{
		if (token_tab[i]->str[0] == '>')
			redir_nb++;
		i++;
	}
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

	i = 0;
	redir_nb = 0;
	redir_path = NULL;
	while (token_tab[i])
	{
		if (token_tab[i]->str[0] == '<')
			redir_nb++;
		i++;
	}
	i = 0;
	j = 0;
	while (token_tab[i] && j < redir_nb)
	{
		if (token_tab[i]->str[0] == '<')
			j++;
		if (j == redir_nb)
			redir_path = get_redir(token_tab[i]->str);
		i++;
	}
	return (redir_path);
}

static char	*get_redir_type(t_token **token_tab)
{
	char	*type;
	int		i;
	int		j;
	int		redir_nb;

	i = 0;
	redir_nb = 0;
	while (token_tab[i])
	{
		if (token_tab[i]->str[0] == '>')
			redir_nb++;
		i++;
	}
	i = 0;
	j = 0;
	while (token_tab[i] && j < redir_nb)
	{
		if (token_tab[i]->str[0] == '>')
			j++;
		if (j == redir_nb)
		{
			if (token_tab[i]->str[1] == '>')
				type = ft_strdup("A");
			else
				type = ft_strdup("T");
		}	
		i++;
	}
	return (type);
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
		ft_printf_fd(1, "%s\n%s\n%s\n", parsed_tree->tab_str[0], parsed_tree->tab_str[1], parsed_tree->tab_str[2]);
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
