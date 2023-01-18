/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:23:19 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/18 11:07:20 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	ft_putnbr(unsigned long int nb, unsigned int size_base,
				char *base, int fd)
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
		ft_putnbr(n / size_base, size_base, base, fd);
	}
	written_size++;
	write(fd, &rec, 1);
	return (written_size);
}

int	ft_putptr_fd(unsigned long int nb, int fd)
{
	int				written_size;

	if (nb == 0)
	{
		write(fd, "(nil)", 5);
		return (5);
	}
	write(fd, "0x", 2);
	written_size = 2;
	written_size += ft_putnbr(nb, 16, "0123456789abcdef", fd);
	return (written_size);
}
