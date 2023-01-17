/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:11:35 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/17 15:44:39 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strndup(const char *str, size_t n)
{
	size_t	pos;
	char	*new;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	if (n < 0 || n > ft_strlen(str))
		n = ft_strlen(str);
	new = malloc((n + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	new[n] = '\0';
	pos = 0;
	while (pos < n)
	{
		new[pos] = str[pos];
		pos++;
	}
	return (new);
}
