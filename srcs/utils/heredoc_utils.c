/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:30:36 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/10 13:36:36 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

void	delete_tmp(t_token **token_tab)
{
	int	pos;

	if (!token_tab)
		return ;
	pos = 0;
	while (token_tab[pos] != NULL)
	{
		if (ft_strncmp(token_tab[pos]->str, "<< .heredoc_", 12) == 0)
			if (ft_strncmp(&token_tab[pos]->str[ft_strlen(token_tab[pos]->str)
						- 4], ".tmp", 4) == 0)
				unlink(&token_tab[pos]->str[3]);
		pos++;
	}
}

char	*redir_heredoc(t_token **token_tab)
{
	int		redir_nb;
	int		i;
	int		j;
	char	*redir_path;

	redir_nb = heredoc_count(token_tab);
	if (redir_nb == 0)
		return (NULL);
	redir_path = NULL;
	i = 0;
	j = 0;
	while (token_tab[i] && j < redir_nb)
	{
		if (token_tab[i]->token_type == HEREDOC)
			j++;
		if (j < redir_nb)
			i++;
	}
	redir_path = ft_strdup(token_tab[i]->str);
	if (!redir_path)
		return (NULL);
	return (redir_path);
}

int	hdoc_pipe_count(t_token **token_tab)
{
	int		i;
	int		hdoc_nb;
	t_token	**sub_tab;

	i = 0;
	while (token_tab[i] && token_tab[i]->token_type != PIPE)
		i++;
	sub_tab = sub_token_tab(token_tab, 0, i);
	hdoc_nb = heredoc_count(sub_tab);
	free_token(sub_tab);
	return (hdoc_nb);
}

char	*init_heredoc_path(int pipe_nb)
{
	char	*path;
	char	*suffix;

	suffix = ft_strjoin_f(ft_itoa(pipe_nb), ".tmp", 1);
	if (!suffix)
		return (NULL);
	path = ft_strjoin_f(".heredoc_", suffix, 2);
	if (!path)
		return (NULL);
	if (access(path, F_OK) == 0)
	{
		free(path);
		pipe_nb++;
		path = init_heredoc_path(pipe_nb);
	}
	return (path);
}
