/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:37:37 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/25 11:40:13 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

char	**tab_dup(char	**tab_str)
{
	char	**new_tab;
	int		len;
	int		i;

	len = strtab_len(tab_str);
	new_tab = malloc(sizeof(char *) * len + 1);
	if (!new_tab)
		return (NULL);
	i = 0;
	while (tab_str[i])
	{
		new_tab[i] = ft_strdup(tab_str[i]);
		if (!new_tab[i])
		{
			d_tab_free(new_tab);
			return (NULL);
		}
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

size_t	strtab_len(char **str_tab)
{
	int	i;

	i = 0;
	while (str_tab[i])
		i++;
	return (i);
}
