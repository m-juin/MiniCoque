/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:18:38 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/20 17:04:27 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static int	getsize(char *arg)
{
	int	pos;

	pos = 0;
	if (arg[pos] == '-' || arg[pos] == '+')
		pos++;
	return (ft_strlen(arg) - pos);
}

static t_bool	isstrnum(char *arg)
{
	int	pos;

	pos = 0;
	if (arg[pos] == '-' || arg[pos] == '+')
		pos++;
	while (arg[pos] != '\0')
	{
		if (ft_isdigit(arg[pos]) != 1)
			return (FALSE);
		pos++;
	}
	return (TRUE);
}

static t_bool	isvalidlong(char *arg, char *base)
{
	int		pos;
	int		sign;

	pos = 0;
	sign = 0;
	if (arg[pos] == '-' || arg[pos] == '+')
		sign = 1;
	while (arg[pos + sign + 1] != '\0')
	{
		if (arg[pos + sign] > base[pos])
			return (FALSE);
		pos++;
	}
	if (arg[0] == '-' && arg[pos + sign] > (base[pos] + 1))
		return (FALSE);
	else if (arg[0] != '-' && arg[pos + sign] > (base[pos]))
		return (FALSE);
	return (TRUE);
}

static t_bool	isvalidnum(char *arg)
{
	int	size;
	int	start;

	start = 0;
	while (arg[start] == ' ')
		start++;
	size = getsize(&arg[start]);
	if (size > 19 || isstrnum(&arg[start]) == FALSE)
		return (FALSE);
	else if (size < 19)
		return (TRUE);
	return (isvalidlong(&arg[start], "9223372036854775807"));
}

void	ft_exit(char **args)
{
	int	tmp;

	ft_printf_fd(1, "exit\n");
	if (args[1] == NULL)
		exit(0);
	else if (args[2] != NULL)
	{
		ft_printf_fd(2, "exit: too many arguments\n");
		return ;
	}
	else if (isvalidnum(args[1]) == FALSE)
	{
		ft_printf_fd(2, "exit: %s: numeric argument required\n", args[1]);
		exit(2);
	}
	tmp = ft_atoll(args[1]);
	tmp = tmp % 256;
	exit(tmp);
}
