/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:42:45 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/16 16:27:00 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static int	check_newline(char *arg)
{
	int	pos;

	if (arg[0] == '-')
	{
		pos = 1;
		while (arg[pos] == 'n')
			pos++;
		if (arg[pos] == '\0' && pos > 1)
			return (-1);
		else
			return (1);
	}
	else
		return (1);
}

int	echo(char **args)
{
	int	pos;
	int	newline;

	if (args[1] == NULL)
	{
		printf("\n");
		return (0);
	}
	newline  = check_newline(args[1]);
	if (newline == -1)
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
	if (newline == 1)
		printf ("\n");
	return (0);
}