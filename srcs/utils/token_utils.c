/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:48:23 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/10 13:30:37 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

int	token_tab_len(t_token **tab, int redir)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (tab[i])
	{
		if (redir == 0 && tab[i]->str)
			len++;
		else
		{
			if (tab[i]->token_type != REDIRECT && tab[i]->token_type != HEREDOC
				&& tab[i]->str)
				len++;
		}
		i++;
	}
	return (len);
}

int	token_empty_tab_len(t_token **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	*free_token(t_token **token_tab)
{
	int		i;

	i = 0;
	while (token_tab[i])
	{
		free(token_tab[i]->str);
		token_tab[i]->str = NULL;
		free(token_tab[i]);
		token_tab[i] = NULL;
		i++;
	}
	free(token_tab);
	token_tab = NULL;
	return (NULL);
}

t_token	**init_tokentab(char *input)
{
	t_token	**token_tab;
	int		i;
	int		nb;

	nb = token_count(input);
	if (nb < 1)
		return (NULL);
	token_tab = ft_calloc(nb + 1, sizeof(t_token *));
	if (!token_tab)
		return (NULL);
	i = 0;
	while (i < nb)
	{
		token_tab[i] = ft_calloc(1, sizeof(t_token));
		if (!token_tab[i])
		{
			token_tab = free_token(token_tab);
			return (NULL);
		}
		token_tab[i]->str = NULL;
		i++;
	}
	token_tab[i] = NULL;
	return (token_tab);
}
