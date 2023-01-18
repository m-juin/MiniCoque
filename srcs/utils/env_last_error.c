/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_last_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:18:55 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/18 14:29:12 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

int last_error(int get, int error)
{
	static int lasterror;

	if (get == 1)
		return (lasterror);
	lasterror = error;
	return (lasterror);
}