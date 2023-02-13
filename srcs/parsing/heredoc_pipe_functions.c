/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pipe_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:38:55 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/13 10:11:58 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static int	find_prev_pipe(t_token **token_tab, int i)
{
	if (!token_tab)
		return (-1);
	while (i > 0 && token_tab[i]->token_type != PIPE)
		i--;
	return (i);
}

static int	hdoc_pipe(t_token **token_tab, int hdoc_values[2], int i)
{
	int		tab_lims[2];
	char	*tmp;

	if (!token_tab)
		return (-1);
	tab_lims[1] = i;
	tab_lims[0] = find_prev_pipe(token_tab, i);
	if (tab_lims[0] == -1)
		return (-1);
	if (token_tab[i]->token_type == HEREDOC)
		hdoc_values[1]++;
	if (hdoc_values[1] == hdoc_values[0])
	{
		tmp = token_tab[i]->str;
		token_tab[i]->str = get_heredoc_path(token_tab, tab_lims);
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

static int	hdoc_pipe_loop(t_token **token_tab, int *hdoc_values, int *i)
{
	int	ret;

	if (!token_tab)
		return (-1);
	ret = 0;
	if (token_tab[*i]->token_type == PIPE)
	{
		hdoc_values[1] = 0;
		(*i)++;
		hdoc_values[0] = hdoc_pipe_count(&token_tab[*i]);
		if (hdoc_values[0] == -1)
			return (-1);
	}
	if (hdoc_values[0] > 0)
		ret = hdoc_pipe(token_tab, hdoc_values, *i);
	return (ret);
}

static int	hdoc_pipe_process(t_token **token_tab, int hdoc_values[2])
{
	int	i;
	int	err;

	i = 0;
	hdoc_values[1] = 0;
	while (token_tab[i])
	{
		err = hdoc_pipe_loop(token_tab, hdoc_values, &i);
		if (err == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	pipe_heredoc(t_token **token_tab)
{
	int		hdoc_values[2];
	int		i;
	int		ret;
	t_token	**sub_tab;

	if (!token_tab)
		return (-1);
	i = 0;
	while (token_tab[i] && token_tab[i]->token_type != PIPE)
		i++;
	sub_tab = sub_token_tab(token_tab, 0, i);
	hdoc_values[0] = heredoc_count(sub_tab);
	free_token(sub_tab);
	if (hdoc_values[0] == -1)
		return (-1);
	ret = hdoc_pipe_process(token_tab, hdoc_values);
	return (ret);
}
