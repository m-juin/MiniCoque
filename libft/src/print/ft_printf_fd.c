/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:14:30 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/26 15:26:27 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	flag_checker(char *s, va_list va, int fd)
{
	int		ptd_cha;

	ptd_cha = 0;
	if (*s == 'c')
		ptd_cha += ft_putchar_fd(va_arg(va, int), fd);
	else if (*s == 's')
		ptd_cha += ft_putstr_fd((char *)va_arg(va, char *), fd);
	else if (*s == 'd' || *s == 'i')
		ptd_cha += ft_putnbr_fd(va_arg(va, int), fd);
	else if (*s == 'u')
		ptd_cha += ft_putnbr_fd((unsigned int)va_arg(va, unsigned int), fd);
	else if (*s == 'x')
		ptd_cha += ft_puthexa_fd(va_arg(va, unsigned int),
				"0123456789abcdef", fd);
	else if (*s == 'X')
		ptd_cha += ft_puthexa_fd(va_arg(va, unsigned int),
				"0123456789ABCDEF", fd);
	else if (*s == 'p')
		ptd_cha += ft_putptr_fd(
				(unsigned long int)va_arg(va, unsigned long int), fd);
	else if (*s == '%')
		ptd_cha += ft_putchar_fd('%', fd);
	else
		s--;
	return (ptd_cha);
}

int	ft_printf_fd(int fd, const char *s, ...)
{
	va_list	var;
	int		written_char;
	char	*str;

	str = (char *)s;
	va_start(var, s);
	written_char = 0;
	while (*str != '\0')
	{
		if (*str != '%')
			written_char += ft_putchar_fd(*str, fd);
		if (*str == '%')
		{
			str++;
			written_char += flag_checker(str, var, fd);
		}
		str++;
	}
	return (written_char);
}
