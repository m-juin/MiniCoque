/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:23:20 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/18 11:04:58 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	ft_printhexa_fd(unsigned int nb, unsigned int size_base, char *base,
						int fd)
{
	int					rec;
	int					j;
	static int			written_size;
	unsigned long int	n;

	j = 0;
	written_size = 0;
	n = nb;
	rec = (n % size_base);
	while (base[j])
	{
		if (rec == j)
			rec = base[j];
		j++;
	}
	if (n >= size_base)
	{	
		ft_printhexa_fd(n / size_base, size_base, base, fd);
	}
	written_size++;
	write(fd, &rec, 1);
	return (written_size);
}

int	ft_puthexa_fd(unsigned int nb, char *base, int fd)
{
	int				i;
	int				j;
	int				written_size;

	i = 0;
	j = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (-1);
		while (j < i)
		{
			if (base[j] == base[i])
				return (-1);
			j++;
		}
		j = 0;
		i++;
	}
	written_size = 0;
	if (i >= 2)
		written_size = ft_printhexa_fd(nb, i, base, fd);
	return (written_size);
}
