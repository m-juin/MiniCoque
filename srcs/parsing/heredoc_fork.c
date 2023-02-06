/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:38:49 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/06 13:38:45 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static char	*get_limiter(char *token)
{
	int		i;
	char	*limiter;

	i = 0;
	while (typify(token[i]) == BLANK || token[i] == '<')
		i++;
	limiter = ft_substr(token, i, ft_strlen(token) - i);
	if (!limiter)
		return (NULL);
	return (limiter);
}

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

static void	prompt_loop(int fd, char *tmp, char *limiter)
{
	int	dupped;

	dupped = dup(0);
	while (tmp[0] == '\0'
		|| ft_strncmp(tmp, limiter, ft_strlen(limiter)) != 0)
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
	dup2(dupped, 0);
	close(dupped);
	free(limiter);
	free(tmp);
}

static void	prompt_prepare(char *path, t_token **token, int i)
{
	char	*limiter;
	char	*tmp;
	int		fd;

	fd = open_tmp_file(path);
	limiter = get_limiter(token[i]->str);
	if (!limiter)
	{
		close(0);
		close(fd);
		free_token(token);
		exit(EXIT_FAILURE);
	}
	tmp = "";
	prompt_loop(fd, tmp, limiter);
	close(fd);
}

void	read_heredoc(t_token **token_tab, int tab_lims[2], char *path,
		t_minicoque *data)
{
	signal(SIGINT, hsighandler);
	while (token_tab[tab_lims[0]] && tab_lims[0] <= tab_lims[1])
	{
		if (token_tab[tab_lims[0]]->str[0] == '<'
			&& token_tab[tab_lims[0]]->str[1] == '<')
			prompt_prepare(path, token_tab, tab_lims[0]);
		tab_lims[0]++;
	}
	free_coque_data(data);
	free(path);
	free_token(token_tab);
	close(0);
	exit(EXIT_SUCCESS);
}
