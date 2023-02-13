/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:38:49 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/13 11:34:56 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static void	end_prompt_loop(int dup, char *limiter, char *tmp)
{
	int			err;
	struct stat	statbuf;

	err = fstat(0, &statbuf);
	if (err == -1)
		dup2(dup, 0);
	close(dup);
	free(limiter);
	free(tmp);
}

static int	hdoc_signals(int dupped, char *limiter, char *tmp, int fd)
{
	int			err;
	struct stat	statbuf;

	err = fstat(0, &statbuf);
	if (err == -1)
	{
		close(fd);
		end_prompt_loop(dupped, limiter, tmp);
		return (-1);
	}
	ft_printf_fd(1, "MiniCoque: warning: here-document \
delimited by end-of-file (wanted `%s')\n", limiter);
	return (0);
}

static int	prompt_loop(int fd, char *limiter, t_bool boo)
{
	char		*tmp;
	int			dupped;

	dupped = dup(0);
	while (boo == TRUE)
	{
		tmp = readline(" > ");
		if (tmp == NULL)
		{
			if (hdoc_signals(dupped, limiter, tmp, fd) == -1)
				return (-1);
			break ;
		}
		if (ft_strcmp(tmp, limiter) != 0)
		{
			tmp = ft_strjoin_f(tmp, "\n", 1);
			ft_putstr_fd(tmp, fd);
			free(tmp);
		}
		else
			boo = FALSE;
	}
	end_prompt_loop(dupped, limiter, tmp);
	return (0);
}

static int	prompt_prepare(char *path, t_token **token, int i)
{
	char	*limiter;
	int		fd;
	int		err;

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(path);
		return (-1);
	}
	limiter = ft_strdup(token[i]->str);
	if (!limiter)
	{
		close(fd);
		return (-1);
	}
	err = prompt_loop(fd, limiter, TRUE);
	if (err == -1)
		return (-1);
	close(fd);
	return (0);
}

int	read_heredoc(t_token **token_tab, int tab_lims[2], char *path)
{
	int	ret;

	ret = 0;
	signal(SIGINT, hsighandler);
	while (token_tab[tab_lims[0]] && tab_lims[0] <= tab_lims[1])
	{
		if (token_tab[tab_lims[0]]->token_type == HEREDOC)
			ret = prompt_prepare(path, token_tab, tab_lims[0]);
		if (ret == -1)
			return (ret);
		tab_lims[0]++;
	}
	return (ret);
}
