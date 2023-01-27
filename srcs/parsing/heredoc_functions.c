/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:12:21 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/27 14:53:58 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <minicoque.h>
#include <sys/wait.h>

static char	*init_heredoc_path(int pipe_nb)
{
	char	*path;
	char	*suffix;

	suffix = ft_strjoin(ft_itoa(pipe_nb), ".tmp");
	if (!suffix)
		return (NULL);
	path = ft_strjoin(".heredoc_", suffix);
	free(suffix);
	if (!path)
		return (NULL);
	path = ft_strjoin("<< ", path);
	return (path);
}

static char	*get_limiter(char *token)
{
	int		i;
	char	*limiter;

	i = 0;
	while (typify(token[i]) == BLANK || token[i] == '<')
		i++;
	limiter = (ft_substr(token, i, ft_strlen(token) - i));
	if (!limiter)
		return (NULL);
	return (limiter);
}

static void	read_heredoc(t_token **token_tab, char *path)
{
	int		i;
	int		fd;
	char	*tmp;
	char	*limiter;

	i = 0;
	while (token_tab[i])
	{
		if (token_tab[i]->str[0] == '<' && token_tab[i]->str[1] == '<')
		{
			fd = open(path, O_RDONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				free(path);
				exit(EXIT_FAILURE);
			}
			limiter = get_limiter(token_tab[i]->str);
			if (!limiter)
				exit(EXIT_FAILURE);
			tmp = "";
			while (tmp[0] == '\0' || ft_strncmp(tmp, limiter, ft_strlen(limiter)) != 0)
			{
				ft_putstr_fd(">", 1);
				if (tmp[0] != '\0')
					free(tmp);
				tmp = get_next_line(0);
				if (ft_strncmp(tmp, limiter, ft_strlen(limiter)) != 0)
					ft_putstr_fd(tmp, fd);
			}
			free(limiter);
			free(tmp);
		}
		i++;
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
	return (path);
}

void	heredoc(t_token **token_tab)
{
	int		i;
	int		j;
	int		start;
	int		pipe_count;

	i = 0;
	j = 1;
	start = 0;
	pipe_count = pipe_token_count(token_tab);
	if (pipe_count == 0)
		token_tab[i]->str = get_heredoc_path(token_tab, j);
	while (token_tab[i])
	{
		if (token_tab[i]->token_type == PIPE)
		{
			token_tab[i]->str = get_heredoc_path(sub_token_tab(token_tab, start, i), j);
			if (!token_tab[i]->str)
				return ;
			j++;
			start = i;
		}
		i++;
	}
}
