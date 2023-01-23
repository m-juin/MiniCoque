/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:47:55 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/23 11:12:26 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

void	s_free(void *elem)
{
	if (elem != NULL)
		free(elem);
}

void	d_tab_free(char **elem)
{
	int	pos;

	pos = 0;
	if (elem == NULL)
		return ;
	while (elem[pos] != NULL)
	{
		s_free(elem[pos]);
		pos++;
	}
	free(elem[pos]);
}

void	free_coque_data(t_minicoque *data)
{
	t_env_var *tmp;
	while (data->env_var != NULL)
	{
		tmp = data->env_var->next;
		s_free(data->env_var->value);
		s_free(data->env_var->name);
		s_free(data->env_var);
		data->env_var = tmp;
	}
	s_free(data);
}