/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:48:23 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/17 17:48:59 by gpasquet         ###   ########.fr       */
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
