/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:12:21 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/03 11:43:02 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static char	*wait_hdoc(char *path, int pid)
{
	int		status;

	waitpid(pid, &status, 0);
	if (!path)
		return (NULL);
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

char	*get_heredoc_path(t_token **token_tab, int pipe_nb)
{
	char	*path;
	int		pid;

	if (!token_tab)
		return (NULL);
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
	path = wait_hdoc(path, pid);
	return (path);
}

static int	no_pipe_heredoc(t_token **token_tab, int heredoc_nb)
{
	int		i;
	int		j;
	char	*path;

	if (!token_tab)
		return (-1);
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
