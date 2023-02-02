/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:11:12 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/02 15:42:15 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	handle_error(const char *s1, const char *s2)
{
	if (s1 == NULL && s2 == NULL)
		return (0);
	else if (s1 == NULL)
		return (s2[0] * -1);
	else
		return (s1[0]);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	long unsigned int	i;
	int					a;
	int					b;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (handle_error(s1, s2));
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
		{	
			a = s1[i];
			if (a < 0)
				a += 256;
			a = a % 256;
			b = s2[i];
			if (b < 0)
				b += 256;
			b = b % 256;
			return (a - b);
		}
		i++;
	}
	return (0);
}
