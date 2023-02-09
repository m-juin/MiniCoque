/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:38:49 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/09 17:40:43 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static void	end_prompt_loop(int dup, char *limiter, char *tmp)
{
	dup2(dup, 0);
	close(dup);
	free(limiter);
	free(tmp);
}

static void	prompt_loop(int fd, char *tmp, char *limiter)
{
	int	dupped;

	dupped = dup(0);
	while ((tmp[0] == '\0'
			|| ft_strncmp(tmp, limiter, ft_strlen(tmp)) != 0))
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
		if (ft_strncmp(tmp, limiter, ft_strlen(tmp)) != 0)
		{
			tmp = ft_strjoin(tmp, "\n");
			ft_putstr_fd(tmp, fd);
		}
	}
	end_prompt_loop(dupped, limiter, tmp);
}

static int	prompt_prepare(char *path, t_token **token, int i)
{
	char	*limiter;
	char	*tmp;
	int		fd;

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(path);
		return (-1);
	}
	limiter = get_limiter(token[i]->str);
	if (!limiter)
	{
		close(fd);
		return (-1);
	}
	tmp = "";
	prompt_loop(fd, tmp, limiter);
	close(fd);
	return (0);
}

int	read_heredoc(t_token **token_tab, int tab_lims[2], char *path)
{
	int	ret;

	signal(SIGINT, hsighandler);
	while (token_tab[tab_lims[0]] && tab_lims[0] <= tab_lims[1])
	{
		if (token_tab[tab_lims[0]]->str[0] == '<'
			&& token_tab[tab_lims[0]]->str[1] == '<')
			ret = prompt_prepare(path, token_tab, tab_lims[0]);
		tab_lims[0]++;
	}
	return (ret);
}
