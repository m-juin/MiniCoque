/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:05:26 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/20 17:11:47 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

long long int	ft_atoll(const char *nptr)
{
	int				i;
	long long int	ret;
	int				sign;

	i = 0;
	ret = 0;
	sign = 1;
	while ((nptr[i] > 8 && nptr[i] < 14) || nptr[i] == ' ')
		i++;
	if (ft_strcmp(&nptr[i], "-9223372036854775808") == 0)
		return (LONG_MIN);
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nptr[i] > 47 && nptr[i] < 58)
	{
		ret = (ret * 10) + (nptr[i] - 48);
		i++;
	}
	ret *= sign;
	return (ret);
}
