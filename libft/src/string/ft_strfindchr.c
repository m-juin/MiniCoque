/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfindchr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:26:30 by mjuin             #+#    #+#             */
/*   Updated: 2023/02/09 16:19:17 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_strfindchr(const char *str, const char c)
{
	int	pos;

	pos = 0;
	if (str == NULL)
		return (-1);
	if (c == '\0')
		return (-1);
	while (str[pos])
	{
		if (str[pos] == c)
			return (pos);
		pos++;
	}
	return (0);
}
