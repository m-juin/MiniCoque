/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:47:55 by mjuin             #+#    #+#             */
/*   Updated: 2023/02/03 13:45:08 by mjuin            ###   ########.fr       */
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
	t_env_var	*tmp;

	if (data == NULL)
		return ;
	while (data->env_var != NULL)
	{
		tmp = data->env_var->next;
		s_free(data->env_var->value);
		s_free(data->env_var->name);
		s_free(data->env_var);
		data->env_var = tmp;
	}
	s_free(data->curprocess);
	s_free(data->prompt);
	s_free(data);
}

void	free_tree(t_btree *root)
{
	int	pos;

	pos = 0;
	if (root == NULL)
		return ;
	if (root->left != NULL)
		free_tree(root->left);
	if (root->right != NULL)
		free_tree(root->right);
	if (root->tab_str == NULL)
		return ;
	while ((root->type == COMMAND && pos < 4)
		|| (root->type != COMMAND && root->tab_str[pos] != NULL))
	{
		if (root->tab_str[pos] != NULL)
			free(root->tab_str[pos]);
		root->tab_str[pos] = NULL;
		pos++;
	}
	if (root->tab_str != NULL)
		free(root->tab_str);
	free(root);
}

void	ft_global_free(t_minicoque *data)
{
	if (data->root != NULL)
		free_tree(data->root);
	free_coque_data(data);
}
