/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:48:23 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/18 10:21:30 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

void	free_token(t_token **token_tab)
{
	int	i;

	i = 0;
	while (token_tab[i])
	{
		free(token_tab[i]->token);
		free(token_tab[i]);
		i++;
	}
	free(token_tab);
}

t_token	**init_tokentab(int token_nb)
{
	t_token	**token_tab;
	int		i;

	token_tab = ft_calloc(token_nb + 1, sizeof(t_token *));
	if (!token_tab)
		return (NULL);
	i = 0;
	while (i < token_nb)
	{
		token_tab[i] = ft_calloc(1, sizeof(t_token));
		if (!token_tab[i])
		{
			free_token(token_tab);
			return (NULL);
		}
		i++;
	}
	token_tab[i] = NULL;
	return (token_tab);
}
