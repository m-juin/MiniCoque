/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:42:45 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/30 16:35:41 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static t_bool	check_newline(char *arg)
{
	int	pos;

	if (arg[0] == '-')
	{
		pos = 1;
		while (arg[pos] == 'n')
			pos++;
		if (arg[pos] == '\0' && pos > 1)
			return (FALSE);
		else
			return (TRUE);
	}
	else
		return (TRUE);
}

int	echo(char **args)
{
	int	pos;
	int	newline;

	if (args[1] == NULL)
	{
		ft_printf_fd(1, "\n");
		last_exit(FALSE, 0);
		return (0);
	}
	newline = check_newline(args[1]);
	if (newline == FALSE)
		pos = 2;
	else
		pos = 1;
	while (args[pos])
	{
		ft_printf_fd(1, "%s", args[pos]);
		pos++;
		if (args[pos] != NULL)
			ft_printf_fd(1, " ");
	}
	if (newline == TRUE)
		ft_printf_fd (1, "\n");
	last_exit(FALSE, 0);
	return (0);
}
