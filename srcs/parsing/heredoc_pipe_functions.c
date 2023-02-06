/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pipe_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:38:55 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/06 11:51:36 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static void	delete_tmp(t_token **token_tab)
{
	int	pos;

	if (!token_tab)
		return ;
	pos = 0;
	while (token_tab[pos] != NULL)
	{
		if (ft_strncmp(token_tab[pos]->str, "<< .heredoc_", 12) == 0)
			if (ft_strncmp(&token_tab[pos]->str[ft_strlen(token_tab[pos]->str)
						- 4], ".tmp", 4) == 0)
				unlink(&token_tab[pos]->str[3]);
		pos++;
	}
}

static int	find_prev_pipe(t_token **token_tab, int i)
{
	if (!token_tab)
		return (-1);
	while (i > 0 && token_tab[i]->token_type != PIPE)
		i--;
	return (i);
}

static int	hdoc_pipe(t_token **token_tab, int pipe_count, int hdoc_values[2], int i, t_minicoque *data)
{
	int		tab_lims[2];
	char	*tmp;

	if (!token_tab)
		return (-1);
	tab_lims[1] = i;
	tab_lims[0] = find_prev_pipe(token_tab, i);
	if (tab_lims[0] == -1)
		return (-1);
	if (token_tab[i]->token_type == REDIRECT && token_tab[i]->str[0]
		== '<' && token_tab[i]->str[1] == '<')
		hdoc_values[1]++;
	if (hdoc_values[1] == hdoc_values[0])
	{
		tmp = token_tab[i]->str;
		token_tab[i]->str = get_heredoc_path(token_tab, tab_lims, pipe_count, data);
		free(tmp);
		hdoc_values[1] = 0;
		if (token_tab[i]->str == NULL)
		{
			delete_tmp(token_tab);
			return (-1);
		}
	}
	return (1);
}

static int	hdoc_pipe_loop(t_token **token_tab, int *hdoc_values, int *i, int pipe_count, t_minicoque *data)
{
	if (!token_tab)
		return (-1);
	if (token_tab[*i]->token_type == PIPE)
	{
		hdoc_values[1] = 0;
		pipe_count++;
		(*i)++;
		hdoc_values[0] = hdoc_pipe_count(&token_tab[*i]);
		if (hdoc_values[0] == -1)
			return (-1);
	}
	if (hdoc_values[0] > 0)
		pipe_count = hdoc_pipe(token_tab, pipe_count, hdoc_values, *i, data);
	return (pipe_count);
}

int	pipe_heredoc(t_token **token_tab, t_minicoque *data)
{
	int		pipe_count;
	int		hdoc_values[2];
	int		i;
	int		start;
	t_token	**sub_tab;

	if (!token_tab)
		return (-1);
	i = 0;
	start = i;
	pipe_count = 0;
	while (token_tab[i] && token_tab[i]->token_type != PIPE)
		i++;
	sub_tab = sub_token_tab(token_tab, 0, i);
	hdoc_values[0] = heredoc_count(sub_tab);
	free_token(sub_tab);
	if (hdoc_values[0] == -1)
		return (-1);
	i = 0;
	hdoc_values[1] = 0;
	while (token_tab[i])
	{
		pipe_count = hdoc_pipe_loop(token_tab, hdoc_values, &i, pipe_count, data);
		if (pipe_count == -1)
			return (-1);
		i++;
	}
	return (0);
}
