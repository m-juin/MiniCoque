/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:12:21 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/06 14:11:15 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static char	*wait_hdoc(char *path, int pid)
{
	int		status;
	char	*tmp;

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
	tmp = path;
	path = ft_strjoin("<< ", path);
	free(tmp);
	return (path);
}

char	*get_heredoc_path(t_token **token_tab, int tab_lims[2],
		t_minicoque *data)
{
	char	*path;
	int		pid;

	if (!token_tab)
		return (NULL);
	path = init_heredoc_path(0);
	if (!path)
		return (NULL);
	pid = fork();
	if (pid == -1)
	{
		free(path);
		return (NULL);
	}
	if (pid == 0)
		read_heredoc(token_tab, tab_lims, path, data);
	path = wait_hdoc(path, pid);
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

static int	no_pipe_heredoc(t_token **token_tab, int heredoc_nb,
		t_minicoque *data)
{
	int		hdoc_index;
	int		tab_lims[2];
	char	*path;

	if (!token_tab || !data)
		return (-1);
	hdoc_index = get_last_hdoc_nb(token_tab, heredoc_nb);
	tab_lims[0] = 0;
	tab_lims[1] = token_tab_len(token_tab, 0);
	path = get_heredoc_path(token_tab, tab_lims, data);
	if (path == NULL)
		return (-1);
	free(token_tab[hdoc_index]->str);
	token_tab[hdoc_index]->str = ft_strdup(path);
	free(path);
	return (1);
}

int	heredoc(t_token **token_tab, t_minicoque *data)
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
		ret = no_pipe_heredoc(token_tab, heredoc_nb, data);
	else
		ret = pipe_heredoc(token_tab, data);
	return (ret);
}
