/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:23:46 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/30 16:37:02 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

int	pwd()
{
	char	*current;

	current = malloc(PATH_MAX * sizeof(char));
	getcwd(current, PATH_MAX);
	ft_printf_fd(1, "%s\n", current);
	free(current);
	last_exit(FALSE, 0);
	return (0);
}
