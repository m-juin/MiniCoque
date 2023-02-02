/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:38:49 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/01 15:52:19 by mjuin            ###   ########.fr       */
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
	limiter = (ft_substr(token, i, ft_strlen(token) - i));
	if (!limiter)
		return (NULL);
	limiter = ft_strjoin(limiter, "\n");
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
	char *sublimiter;

	sublimiter = ft_substr(limiter, 0, ft_strlen(limiter) - 1);
	while (tmp[0] == '\0'
		|| ft_strncmp(tmp, limiter, ft_strlen(limiter)) != 0)
	{
		ft_putstr_fd(">", 1);
		if (tmp[0] != '\0')
			free(tmp);
		tmp = get_next_line(0);
		if (tmp == NULL)
			ft_printf_fd(1, "MiniCoque: warning: here-document delimited by end-of-file (wanted `%s')\n", sublimiter);
		if (ft_strncmp(tmp, limiter, ft_strlen(limiter)) != 0)
			ft_putstr_fd(tmp, fd);
	}
	free(sublimiter);
	free(limiter);
	free(tmp);
}

void	hsighandler()
{
	ft_putstr_fd("\n", 1);
	exit(2);
}

void	read_heredoc(t_token **token_tab, char *path)
{
	int		i;
	int		fd;
	char	*tmp;
	char	*limiter;

	i = 0;
	signal(SIGINT, hsighandler);
	while (token_tab[i])
	{
		if (token_tab[i]->str[0] == '<' && token_tab[i]->str[1] == '<')
		{
			fd = open_tmp_file(path);
			limiter = get_limiter(token_tab[i]->str);
			if (!limiter)
				exit(EXIT_FAILURE);
			tmp = "";
			prompt_loop(fd, tmp, limiter);
			close(fd);
		}
		i++;
	}
	exit(EXIT_SUCCESS);
}
