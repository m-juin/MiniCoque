/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:16:31 by mjuin             #+#    #+#             */
/*   Updated: 2023/02/02 10:21:40 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

int isfile(const char* name)
{
	DIR* directory = opendir(name);

	if(directory != NULL)
	{
		closedir(directory);
		return 0;
	}
	if(errno == ENOTDIR)
		return 1;
	return -1;
}