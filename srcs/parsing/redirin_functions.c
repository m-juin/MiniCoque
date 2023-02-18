/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 09:43:42 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/18 13:35:56 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

t_bool	check_redirin(t_token *token, char **redir_tab)
{
	char	*path;

	if (!token)
		return (FALSE);
	path = get_redir(token->str);
	if (!path)
		return (FALSE);
	if (access(path, R_OK) != 0)
	{
		free(*redir_tab);
		*redir_tab = path;
		return (FALSE);
	}
	free(path);
	return (TRUE);
}

t_bool	get_redirin(t_token *token, char **redir_path)
{
	int	fd;

	if (!token || !redir_path)
		return (FALSE);
	if (*redir_path)
		free(*redir_path);
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

int	open_redir_in(t_token **token_tab)
{
	int		i;
	int		fd;
	char	*path;

	i = 0;
	while (token_tab[i])
	{
		if (token_tab[i]->token_type == REDIRECT && token_tab[i]->str[0] == '<'
			&& token_tab[i]->str[1] == '>')
		{
			path = get_redir(token_tab[i]->str);
			if (access(path, F_OK) != 0)
			{
				fd = open(path, O_CREAT, 0644);
				if (fd == -1)
					return (-1);
				close(fd);
			}
			free (path);
		}
		i++;
	}
	return (0);
}
