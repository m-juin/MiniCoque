/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:23:46 by mjuin             #+#    #+#             */
/*   Updated: 2023/02/10 11:03:31 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

int	pwd(void)
{
	char	*current;

	current = malloc(PATH_MAX * sizeof(char));
	getcwd(current, PATH_MAX);
	ft_printf_fd(1, "%s\n", current);
	free(current);
	g_exit_code = 0;
	return (0);
}
