/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_mega_join.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:34:38 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/20 10:17:40 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static size_t	get_arg_size(const char *arg)
{
	size_t	size;

	size = 0;
	if (arg == NULL)
		return (0);
	while (arg[size])
		size++;
	return (size);
}

static int	copyarg(char *str, char *arg)
{
	size_t	pos;

	pos = 0;
	if (str == NULL || arg == NULL)
		return (0);
	while (arg[pos] != '\0')
	{
		str[pos] = arg[pos];
		pos++;
	}
	return (pos);
}

static char	*get_new_str(size_t size, const char *str, va_list lst)
{
	size_t	pos;
	size_t	pos2;
	char	*new;

	pos = 0;
	if (str == NULL || size <= 0)
		return (NULL);
	new = malloc(size * sizeof(char));
	if (new == NULL)
		return (NULL);
	new[size - 1] = '\0';
	pos2 = 0;
	while (str[pos])
	{
		if (str[pos] == '%' && str[pos + 1] == 's')
		{
			pos2 += copyarg(&new[pos2], va_arg(lst, char *));
			pos++;
		}
		else
			new[pos2++] = str[pos];
		pos++;
	}
	return (new);
}

static size_t	sizecount(const char *str, va_list lst)
{
	size_t	pos;
	size_t	size;

	pos = 0;
	size = 0;
	if (str == NULL)
		return (0);
	while (str[pos])
	{
		if (str[pos] == '%' && str[pos + 1] == 's')
		{
			size += get_arg_size(va_arg(lst, char *));
			pos++;
		}
		else
			size++;
		pos++;
	}
	return (size + 1);
}

char	*ft_str_mega_join(const char *str, ...)
{
	va_list	arglist;
	char	*new;
	size_t	size;

	if (str == NULL)
		return (NULL);
	va_start(arglist, str);
	size = sizecount(str, arglist);
	va_end(arglist);
	va_start(arglist, str);
	new = get_new_str(size, str, arglist);
	va_end(arglist);
	if (new == NULL)
		return (NULL);
	return (new);
}
