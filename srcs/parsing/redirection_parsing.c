/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 09:20:44 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/02 11:47:59 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static void	delete_files(t_token **token_tab)
{
	int		i;
	char	*path;

	i = 0;
	while (token_tab[i])
	{
		if (token_tab[i]->token_type == REDIRECT && token_tab[i]->str[0] == '>')
		{
			path = get_redir(token_tab[i]->str);
			if (access(path, F_OK) == 0)
				unlink(path);
		}
		i++;
	}
}

static t_bool	get_redirout_path(t_token **token, int i, char **redir_path)
{
	int		fd;

	*redir_path = get_redir(token[i]->str);
	if (access(*redir_path, F_OK) != 0)
	{
		fd = open(*redir_path, O_CREAT, 0644);
		if (fd == -1)
		{
			delete_files(token);
			return (FALSE);
		}
		close(fd);
	}
	if (access(*redir_path, W_OK) != 0)
	{
		delete_files(token);
		return (FALSE);
	}
	return (TRUE);
}

static char	*redir_out(t_token **token_tab)
{
	int		redir_nb;
	int		i;
	int		j;
	char	*redir_path;

	redir_nb = redir_out_count(token_tab);
	redir_path = NULL;
	i = 0;
	j = 0;
	while (token_tab[i] && j < redir_nb)
	{
		if (token_tab[i]->token_type == REDIRECT && token_tab[i]->str[0] == '>')
		{
			j++;
			if (redir_path)
				free(redir_path);
			if (get_redirout_path(token_tab, i, &redir_path) == FALSE)
				return (redir_path);
		}
		i++;
	}
	return (redir_path);
}

static t_bool	get_redirin(t_token *token, char **redir_path)
{
	int	fd;

	*redir_path = get_redir(token->str);
	if (access(*redir_path, W_OK) != 0)
	{	
		if (token->str[1] == '>')
		{
			fd = open(*redir_path, O_CREAT, 0644);
			close(fd);
		}
		else
			return (FALSE);
	}
	return (TRUE);
}

static char	*redir_in(t_token **token_tab)
{
	int		redir_nb;
	int		i;
	int		j;
	char	*redir_path;

	redir_path = NULL;
	i = 0;
	j = 0;
	while (token_tab[i] && j < redir_nb)
	{
		if (token_tab[i]->token_type == REDIRECT && token_tab[i]->str[0] == '<')
		{
			j++;
			if (get_redirin(token_tab[i], &redir_path) == FALSE)
				return (redir_path);
		}
		i++;
	}
	return (redir_path);
}

char	**redirtab_create(t_token **token_tab)
{
	char	**redir_tab;
	int		i;

	redir_tab = malloc(sizeof(char *) * 5);
	if (!redir_tab)
		return (NULL);
	redir_tab[0] = redir_heredoc(token_tab);
	if (!redir_tab[0])
		redir_tab[0] = redir_in(token_tab);
	if (!redir_tab[0] || access(redir_tab[0], F_OK | W_OK) == 0)
		redir_tab[1] = redir_out(token_tab);
	else
		redir_tab[1] = NULL;
/*	i = 0;
	while (token_tab[i])
	{
		if (token_tab[i]->str[0] == '<')
			redir_tab[0] = get_redirin()
		if (token_tab[i]->str[0] == '>')
			redir_tab[1] = get_redirout();
		i++;
	}
*/	if (redir_tab[1])
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
