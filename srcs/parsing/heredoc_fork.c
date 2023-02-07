/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:38:49 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/07 17:22:45 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static int	open_tmp_file(char *path)
{
	int	fd;

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(path);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

static void	end_prompt_loop(int dup, char *limiter, char *tmp)
{
	dup2(dup, 0);
	close(dup);
	free(limiter);
	free(tmp);
	free(g_heredoc_data);
}

static void	prompt_loop(int fd, char *tmp, char *limiter)
{
	int	dupped;

	dupped = dup(0);
	g_heredoc_data->fds[1] = dupped;
	while ((tmp[0] == '\0'
			|| ft_strncmp(tmp, limiter, ft_strlen(limiter)) != 0))
	{
		if (tmp[0] != '\0')
			free(tmp);
		tmp = readline(" > ");
		if (tmp == NULL)
		{
			ft_printf_fd(1, "MiniCoque: warning: here-document \
delimited by end-of-file (wanted `%s')\n", limiter);
			break ;
		}
		if (ft_strncmp(tmp, limiter, ft_strlen(limiter)) != 0)
		{
			tmp = ft_strjoin(tmp, "\n");
			ft_putstr_fd(tmp, fd);
		}
	}
	end_prompt_loop(dupped, limiter, tmp);
}

static void	prompt_prepare(char *path, t_token **token, int i)
{
	char	*limiter;
	char	*tmp;
	int		fd;

	fd = open_tmp_file(path);
//	free(path);
	limiter = get_limiter(token[i]->str);
	if (!limiter)
	{
		close(0);
		close(fd);
		free_token(token);
		exit(EXIT_FAILURE);
	}
	tmp = "";
	g_heredoc_data = malloc(1 * sizeof(t_heredoc));
	if (g_heredoc_data == NULL)
		return ;
	g_heredoc_data->fds[0] = fd;
	g_heredoc_data->limiter = limiter;
	g_heredoc_data->tokentab = token;
	g_heredoc_data->hdoc_path = path;
	prompt_loop(fd, tmp, limiter);
	close(fd);
}

void	read_heredoc(t_token **token_tab, int tab_lims[2], char *path,
		t_minicoque *data)
{
	signal(SIGINT, hsighandler);
	free_coque_data(data);
	while (token_tab[tab_lims[0]] && tab_lims[0] <= tab_lims[1])
	{
		if (token_tab[tab_lims[0]]->str[0] == '<'
			&& token_tab[tab_lims[0]]->str[1] == '<')
			prompt_prepare(path, token_tab, tab_lims[0]);
		tab_lims[0]++;
	}
	s_free(path);
	free_token(token_tab);
	close(0);
	exit(EXIT_SUCCESS);
}
