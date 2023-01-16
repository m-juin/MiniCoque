/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:42:45 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/16 12:04:32 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

int	echo(char **args)
{
	int	pos;

	if (args == NULL)
	{
		printf("\n");
		return (0);
	}
	if (args[0] == "-n")
		pos = 1;
	else
		pos = 0;
	while (args[pos])
	{
		printf ("%s", args[pos]);
		pos++;
		if (args[pos] != NULL)
			printf(" ");
	}
	if (args[0] != "-n")
		printf ("\n");
	return (0);
}