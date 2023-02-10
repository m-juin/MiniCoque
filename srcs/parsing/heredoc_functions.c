/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:12:21 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/10 11:24:29 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

char	*get_heredoc_path(t_token **token_tab, int tab_lims[2])
{
	char	*path;
	int		ret;

	if (!token_tab)
		return (NULL);
	path = init_heredoc_path(0);
	if (!path)
		return (NULL);
	ret = read_heredoc(token_tab, tab_lims, path);
	if (ret == -1)
	{
		unlink(path);
		free(path);
		return (NULL);
	}
	path = ft_strjoin_f("<< ", path, 2);
	return (path);
}

static int	get_last_hdoc_nb(t_token **token_tab, int heredoc_nb)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (token_tab[i] && j < heredoc_nb)
	{
		if (token_tab[i]->token_type == REDIRECT && token_tab[i]->str[0]
			== '<' && token_tab[i]->str[1] == '<')
			j++;
		if (j < heredoc_nb)
			i++;
	}
	return (i);
}

static int	no_pipe_heredoc(t_token **token_tab, int heredoc_nb)
{
	int		hdoc_index;
	int		tab_lims[2];
	char	*path;

	if (!token_tab)
		return (-1);
	hdoc_index = get_last_hdoc_nb(token_tab, heredoc_nb);
	tab_lims[0] = 0;
	tab_lims[1] = token_tab_len(token_tab, 0);
	path = get_heredoc_path(token_tab, tab_lims);
	if (path == NULL)
	{
		delete_tmp(token_tab);
		return (-1);
	}
	free(token_tab[hdoc_index]->str);
	token_tab[hdoc_index]->str = ft_strdup(path);
	free(path);
	return (1);
}

int	heredoc(t_token **token_tab)
{
	int	pipe_count;
	int	heredoc_nb;
	int	ret;

	if (!token_tab || !token_tab[0])
		return (0);
	ret = 0;
	heredoc_nb = heredoc_count(token_tab);
	if (heredoc_nb == 0)
		return (0);
	pipe_count = pipe_token_count(token_tab);
	if (pipe_count == 0)
		ret = no_pipe_heredoc(token_tab, heredoc_nb);
	else
		ret = pipe_heredoc(token_tab);
	return (ret);
}
