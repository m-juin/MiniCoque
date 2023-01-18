/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:42:45 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/18 15:54:47 by mjuin            ###   ########.fr       */
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
		return (FALSE);
}

int	echo(char **args)
{
	int	pos;
	int	newline;

	if (args[1] == NULL)
	{
		printf("\n");
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
		printf("%s", args[pos]);
		pos++;
		if (args[pos] != NULL)
			printf(" ");
	}
	if (newline == TRUE)
		printf ("\n");
	last_exit(FALSE, 0);
	return (0);
}
