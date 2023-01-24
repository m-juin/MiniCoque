/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:23:46 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/24 11:30:45 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

int	pwd(int fds[2])
{
	char	*current;

	current = malloc(PATH_MAX * sizeof(char));
	getcwd(current, PATH_MAX);
	ft_printf_fd(fds[1], "%s\n", current);
	free(current);
	last_exit(FALSE, 0);
	return (0);
}
