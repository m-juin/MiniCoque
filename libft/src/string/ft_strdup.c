/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:21:18 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/18 10:54:07 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	int		i;
	char	*new_s;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	new_s = malloc(sizeof(char) * (len + 1));
	if (new_s == 0)
		return (0);
	i = 0;
	while (s[i])
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = 0;
	return (new_s);
}
