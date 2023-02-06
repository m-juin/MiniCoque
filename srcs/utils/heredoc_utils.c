/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:30:36 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/06 10:50:01 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

int	heredoc_count(t_token **token_tab)
{
	int	i;
	int	redir_nb;

	if (!token_tab)
		return (-1);
	redir_nb = 0;
	i = 0;
	while (token_tab[i])
	{
		if (token_tab[i]->token_type == REDIRECT && token_tab[i]->str[0]
			== '<' && token_tab[i]->str[1] == '<')
			redir_nb++;
		i++;
	}
	return (redir_nb);
}

char	*redir_heredoc(t_token **token_tab)
{
	int		redir_nb;
	int		i;
	int		j;
	char	*redir_path;

	redir_nb = heredoc_count(token_tab);
	if (redir_nb == 0)
		return (NULL);
	redir_path = NULL;
	i = 0;
	j = 0;
	while (token_tab[i] && j < redir_nb)
	{
		if (token_tab[i]->token_type == REDIRECT && token_tab[i]->str[0]
			== '<' && token_tab[i]->str[1] == '<')
			j++;
		if (j < redir_nb)
			i++;
	}
	redir_path = get_redir(token_tab[i]->str);
	if (!redir_path)
		return (NULL);
	return (redir_path);
}

int	hdoc_pipe_count(t_token **token_tab)
{
	int		i;
	int		hdoc_nb;
	t_token	**sub_tab;

	i = 0;
	while (token_tab[i] && token_tab[i]->token_type != PIPE)
		i++;
	sub_tab = sub_token_tab(token_tab, 0, i);
	hdoc_nb = heredoc_count(sub_tab);
	free_token(sub_tab);
	return (hdoc_nb);
}

char	*init_heredoc_path(int pipe_nb)
{
	char	*path;
	char	*suffix;

	suffix = ft_strjoin_f(ft_itoa(pipe_nb), ".tmp");
	if (!suffix)
		return (NULL);
	path = ft_strjoin(".heredoc_", suffix);
	if (!path)
		return (NULL);
	free(suffix);
	if (access(path, F_OK) == 0)
	{
		free(path);
		pipe_nb++;
		path = init_heredoc_path(pipe_nb);
	}
	return (path);
}
