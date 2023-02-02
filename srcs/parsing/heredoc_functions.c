/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:12:21 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/02 17:16:06 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static void delete_tmp(t_token **token_tab)
{
	int	pos;

	pos = 0;
	while(token_tab[pos] != NULL)
	{
		printf("tokentab[%i] = %s\n", pos, token_tab[pos]->str);
		if(ft_strncmp(token_tab[pos]->str, "<< .heredoc_", 12) == 0)
			if (ft_strncmp(&token_tab[pos]->str[ft_strlen(token_tab[pos]->str) - 4], ".tmp", 4) == 0)
				unlink(&token_tab[pos]->str[3]);
		pos++;
	}
}

static char	*get_heredoc_path(t_token **token_tab, int pipe_nb)
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
		read_heredoc(token_tab, path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 2)
		{
			unlink(path);
			return (NULL);
		}
	}
	path = ft_strjoin("<< ", path);
	return (path);
}

static int	find_prev_pipe(t_token **token_tab, int i)
{
	while (i > 0 && token_tab[i]->token_type != PIPE)
		i--;
	return (i);
}

static int	hdoc_pipe(t_token **token_tab, int pipe_count, int hdoc_values[2], int i)
{
	int	start;

	start = find_prev_pipe(token_tab , i);
	if (token_tab[i]->token_type == REDIRECT && token_tab[i]->str[0]
		== '<' && token_tab[i]->str[1] == '<')
		hdoc_values[1]++;
	if (hdoc_values[1] == hdoc_values[0])
	{
		token_tab[i]->str = get_heredoc_path(sub_token_tab
				(token_tab, start, i + 1), pipe_count);
		hdoc_values[1] = 0;
		if (token_tab[i]->str == NULL)
		{
			delete_tmp(token_tab);
			return (-1);
		}
	}
	return (1);
}

static int	pipe_heredoc(t_token **token_tab)
{
	int		pipe_count;
	int		hdoc_values[2];
	int		i;
	int		start;
	int		ret;

	i = 0;
	start = i;
	pipe_count = 0;
	while (token_tab[i] && token_tab[i]->token_type != PIPE)
		i++;
	hdoc_values[0] = heredoc_count(sub_token_tab(token_tab, 0, i));
	i = 0;
	hdoc_values[1] = 0;
	while (token_tab[i])
	{
		if (token_tab[i]->token_type == PIPE)
		{
			hdoc_values[1] = 0;
			pipe_count++;
			i++;
			hdoc_values[0] = hdoc_pipe_count(&token_tab[i]);
		}
		if (hdoc_values[0] > 0)
			ret = hdoc_pipe(token_tab, pipe_count, hdoc_values, i);
		if (ret == -1)
			return (-1);
		i++;
	}
	return (0);
}

static int 	no_pipe_heredoc(t_token **token_tab, int heredoc_nb)
{
	int		i;
	int		j;
	char	*path;

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
	path = get_heredoc_path(token_tab, j);
	if (path == NULL)
		return (-1);
	token_tab[i]->str = path;
	return (1);
}

int	heredoc(t_token **token_tab)
{
	int	pipe_count;
	int	heredoc_nb;
	int	ret;
	
	ret = 0;
	if (!token_tab || !token_tab[0])
		return (0);
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
