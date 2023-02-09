/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 09:20:44 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/09 16:25:25 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static t_bool	get_redirout(t_token **token, int i, char **redir_path,
		int redirout_nb)
{
	int		fd;
	int		redirout_tot;

	if (!token || !redir_path)
		return (FALSE);
	redirout_tot = redir_out_count(token);
	if (*redir_path)
		free(*redir_path);
	*redir_path = get_redir(token[i]->str);
	if (token[i]->str[1] == '>')
		fd = open(*redir_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(*redir_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		delete_files(token);
		return (FALSE);
	}
	close(fd);
	if (access(*redir_path, W_OK) != 0)
	{
		redirout_nb = 0;
		return (FALSE);
	}
	return (TRUE);
}

static void	redir_in_n_out(t_token **token_tab, char **redir_tab)
{
	int		i;
	int		redirout_nb;
	t_bool	redir_status;

	if (!token_tab || !redir_tab)
		return ;
	redirout_nb = 1;
	redir_status = TRUE;
	i = 0;
	while (token_tab[i])
	{
		if (redir_status == TRUE && token_tab[i]->token_type == REDIRECT
			&& token_tab[i]->str[0] == '<')
			redir_status = get_redirin(token_tab[i], &redir_tab[0]);
		if (redir_status == TRUE && token_tab[i]->token_type == REDIRECT
			&& token_tab[i]->str[0] == '>')
		{
			redir_status = get_redirout(token_tab, i, &redir_tab[1],
					redirout_nb);
			redirout_nb++;
		}
		i++;
	}
}

static void	redir_only_out(t_token **token_tab, char **redir_tab)
{
	int		i;
	int		redir_nb;
	int		err;
	t_bool	redir_status;

	if (!token_tab || !redir_tab)
		return ;
	err = open_redir_in(token_tab);
	if (err == -1)
		return ;
	redir_nb = 1;
	redir_status = TRUE;
	i = 0;
	while (token_tab[i])
	{
		if (redir_status == TRUE && token_tab[i]->token_type == REDIRECT
			&& token_tab[i]->str[0] == '>')
		{
			redir_status = get_redirout(token_tab, i, &redir_tab[1], redir_nb);
			redir_nb++;
		}
		i++;
	}
}

char	**redirtab_create(t_token **token_tab)
{
	char	**redir_tab;

	if (!token_tab)
		return (NULL);
	redir_tab = malloc(sizeof(char *) * 5);
	if (!redir_tab)
		return (NULL);
	redir_tab[1] = NULL;
	redir_tab[0] = redir_heredoc(token_tab);
	if (redir_tab[0])
		redir_only_out(token_tab, redir_tab);
	else
		redir_in_n_out(token_tab, redir_tab);
	if (redir_tab[1])
		redir_tab[2] = get_redir_type(token_tab);
	else
		redir_tab[2] = NULL;
	if (redir_tab[0] && ft_strncmp(redir_tab[0], ".heredoc_", 9) == 0)
		redir_tab[3] = ft_strdup("DEL");
	else
		redir_tab[3] = ft_strdup("NOT_DEL");
	redir_tab[4] = NULL;
	return (redir_tab);
}
