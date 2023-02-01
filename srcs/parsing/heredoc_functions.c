/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:12:21 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/01 14:40:59 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static char	*get_heredoc_path(t_token **token_tab, int pipe_nb, t_minicoque *data)
{
	char	*path;
	int		pid;
	int		status;

	path = init_heredoc_path(pipe_nb);
	if (!path)
		return (NULL);
	pid = fork();
	if (pid == -1)
	{
		free(path);
		return (NULL);
	}
	if (pid == 0)
		read_heredoc(token_tab, path, data);
	waitpid(pid, &status, 0);
	path = ft_strjoin("<< ", path);
	return (path);
}

static void	hdoc_pipe(t_token **token_tab, int pipe_count, int hdoc_nb, t_minicoque *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (token_tab[i]->token_type == REDIRECT && token_tab[i]->str[0]
		== '<' && token_tab[i]->str[1] == '<')
		j++;
	if (j == hdoc_nb)
	{
		token_tab[i]->str = get_heredoc_path(sub_token_tab
				(token_tab, 0, i + 1), pipe_count, data);
	j = 0;
	}
}

static void	pipe_heredoc(t_token **token_tab, t_minicoque *data)
{
	int		pipe_count;
	int		hdoc_nb;
	int		i;

	i = 0;
	pipe_count = 0;
	while (token_tab[i] && token_tab[i]->token_type != PIPE)
		i++;
	hdoc_nb = heredoc_count(sub_token_tab(token_tab, 0, i));
	i = 0;
	while (token_tab[i])
	{
		if (token_tab[i]->token_type == PIPE)
		{
			pipe_count++;
			i++;
			hdoc_nb = hdoc_pipe_count(&token_tab[i]);
		}
		if (hdoc_nb > 0)
			hdoc_pipe(&token_tab[i], pipe_count, hdoc_nb, data);
		i++;
	}
}

static void	no_pipe_heredoc(t_token **token_tab, int heredoc_nb, t_minicoque *data)
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
	token_tab[i]->str = get_heredoc_path(token_tab, j, data);
}

void	heredoc(t_token **token_tab, t_minicoque *data)
{
	int		pipe_count;
	int		heredoc_nb;

	if (!token_tab || !token_tab[0])
		return ;
	heredoc_nb = heredoc_count(token_tab);
	if (heredoc_nb == 0)
		return ;
	pipe_count = pipe_token_count(token_tab);
	if (pipe_count == 0)
		no_pipe_heredoc(token_tab, heredoc_nb, data);
	else
		pipe_heredoc(token_tab, data);
}
