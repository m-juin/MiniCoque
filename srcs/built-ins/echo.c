/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:42:45 by mjuin             #+#    #+#             */
/*   Updated: 2023/02/10 11:01:22 by mjuin            ###   ########.fr       */
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

static void	print_loop(char **args)
{
	size_t	pos;
	t_bool	check;

	check = TRUE;
	pos = 1;
	while (args[pos])
	{
		if (check == FALSE || check_newline(args[pos]) == TRUE)
		{
			check = FALSE;
			ft_printf_fd(1, "%s", args[pos]);
			if (args[pos + 1] != NULL)
				ft_printf_fd(1, " ");
		}
		pos++;
	}
}

int	echo(char **args)
{
	t_bool	new_line;

	if (args[1] == NULL)
		ft_printf_fd(1, "\n");
	else
	{
		new_line = check_newline(args[1]);
		print_loop(args);
		if (new_line == TRUE)
			ft_printf_fd (1, "\n");
	}
	g_exit_code = 0;
	return (0);
}
