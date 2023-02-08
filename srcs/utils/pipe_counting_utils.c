/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_counting_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:48:23 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/08 11:58:29 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static int	check_bef_aft_pipe(int i, char *input, char *err_msg)
{
	int	j;

	j = i - 1;
	while (j >= 0 && typify(input[j]) == BLANK)
		j--;
	if (j < 0)
	{
		ft_printf_fd(2, "%s `|'\n", err_msg);
		free(err_msg);
		return (-1);
	}
	j = i + 1;
	while (input[j] && typify(input[j]) == BLANK)
		j++;
	if (input[j] == '\0' || input[j] == '|')
	{
		ft_printf_fd(2, "%s `|'\n", err_msg);
		free(err_msg);
		return (-1);
	}
	return (0);
}

int	pipe_count(char *input, int *i, int *nb)
{
	char	*err_msg;

	err_msg = ft_strdup("minicoque: syntax error near unexpected token");
	if (input[*i + 1] == '|' || input[*i + 1] == '\0')
	{
		ft_printf_fd(2, "%s `|'\n", err_msg);
		free(err_msg);
		return (-1);
	}
	if (check_bef_aft_pipe(*i, input, err_msg) == -1)
		return (-1);
	(*nb)++;
	(*i)++;
	free(err_msg);
	return (0);
}

int	pipe_token_count(t_token **token_tab)
{
	int	i;
	int	pipe_count;

	i = 0;
	pipe_count = 0;
	while (token_tab[i])
	{
		if (token_tab[i]->token_type == PIPE)
			pipe_count++;
		i++;
	}
	return (pipe_count);
}
