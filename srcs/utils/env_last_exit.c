/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_last_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:18:55 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/20 10:52:15 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

int	last_exit(t_bool get, int error)
{
	static int	lasterror;

	if (get == TRUE)
		return (lasterror);
	lasterror = error;
	return (lasterror);
}
