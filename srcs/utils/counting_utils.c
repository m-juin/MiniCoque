/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counting_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:43:29 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/24 16:44:00 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

int	pipe_count(char *input, int *i, int *nb)
{
	char	*err_msg;

	err_msg = ft_strdup("minicoque: syntax error nearunexpected token");
	if (input[*i + 1] == '|')
	{
		ft_printf_fd(2, "%s `|'\n", err_msg);
		free(err_msg);
		return (-1);
	}
	(*nb)++;
	(*i)++;
	free(err_msg);
	return (0);
}
