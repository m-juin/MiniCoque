/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:18:38 by mjuin             #+#    #+#             */
/*   Updated: 2023/02/10 11:02:26 by mjuin            ###   ########.fr       */
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

void	ft_exit(char **args, t_minicoque *data)
{
	long long	tmp;

	ft_printf_fd(1, "exit\n");
	tmp = -1;
	if (args == NULL || args[1] == NULL)
		tmp = 0;
	else if (args[2] != NULL)
	{
		ft_printf_fd(2, "exit: too many arguments\n");
		g_exit_code = 1;
		return ;
	}
	else if (isvalidnum(args[1]) == FALSE)
	{
		ft_printf_fd(2, "exit: %s: numeric argument required\n", args[1]);
		tmp = 2;
	}
	if (tmp == -1)
		tmp = ft_atoll(args[1]) % 256;
	ft_global_free(data);
	exit(tmp);
}
