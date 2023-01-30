/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 09:20:44 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/30 11:47:42 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static char	*get_redirout_path(t_token *token)
{
	char	*redir_path;
	int		fd;

	redir_path = get_redir(token->str);
	if (access(redir_path, F_OK) != 0)
	{
		fd = open(redir_path, O_CREAT, 0644);
		close(fd);
	}
	return (redir_path);
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
		if (token_tab[i]->str[0] == '>')
		{
			j++;
			if (redir_path)
				free(redir_path);
			redir_path = get_redirout_path(token_tab[i]);
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

	redir_nb = redir_in_count(token_tab);
	redir_path = NULL;
	i = 0;
	j = 0;
	while (token_tab[i] && j < redir_nb)
	{
		if (token_tab[i]->str[0] == '<')
		{
			j++;
			if (get_redirin(token_tab[i], &redir_path) == FALSE)
				return (redir_path);
		}
		i++;
	}
	return (redir_path);
}

int	heredoc_count(t_token **token_tab)
{
	int	i;
	int	redir_nb;

	redir_nb = 0;
	i = 0;
	while (token_tab[i])
	{
		if (token_tab[i]->str[0] == '<' && token_tab[i]->str[1] == '<')
			redir_nb++;
		i++;
	}
	return (redir_nb);
}

static char	*redir_heredoc(t_token **token_tab)
{
	int		redir_nb;
	int		i;
	int		j;
	char	*redir_path;

	redir_nb = heredoc_count(token_tab);
	redir_path = NULL;
	i = 0;
	j = 0;
	while (token_tab[i] && j < redir_nb)
	{
		if (token_tab[i]->str[0] == '<' && token_tab[i]->str[1] == '<')
			j++;
		if (j < redir_nb)
			i++;
	}
	redir_path = get_redir(token_tab[i]->str);
	if (!redir_path)
		return (NULL);
	return (redir_path);
}

char	**redirtab_create(t_token **token_tab)
{
	char	**redir_tab;

	redir_tab = malloc(sizeof(char *) * 5);
	if (!redir_tab)
		return (NULL);
	redir_tab[0] = redir_heredoc(token_tab);
	if (!redir_tab[0])
		redir_tab[0] = redir_in(token_tab);
	redir_tab[1] = redir_out(token_tab);
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
