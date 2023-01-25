/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:48:23 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/23 15:42:52 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

int	token_tab_len(t_token **tab)
{
	int	len;

	len = 0;
	while (tab[len])
		len++;
	return (len);
}

void	free_token(t_token **token_tab)
{
	int	i;

	i = 0;
	while (token_tab[i])
	{
		free(token_tab[i]->str);
		free(token_tab[i]);
		i++;
	}
	free(token_tab);
}

t_token	**init_tokentab(char *input)
{
	t_token	**token_tab;
	int		i;
	int		nb;

	nb = token_count(input);
	if (nb < 1)
		return (NULL);
	token_tab = ft_calloc(nb + 1, sizeof(t_token *));
	if (!token_tab)
		return (NULL);
	i = 0;
	while (i < nb)
	{
		token_tab[i] = ft_calloc(1, sizeof(t_token));
		if (!token_tab[i])
		{
			free_token(token_tab);
			return (NULL);
		}
		token_tab[i]->str = ft_strdup("");
		i++;
	}
	token_tab[i] = NULL;
	return (token_tab);
}

void	pipe_token(t_token **token_tab, int *i, int *nb)
{
	if (token_tab[*nb]->str[0] != '\0'
		&& digit_str(token_tab[*nb]->str) == 0)
		(*nb)++;
	token_tab[*nb]->str = ft_strdup("|");
	(*i)++;
}

void	redirect_token(t_token **token_tab, char *input, int *i, int *nb)
{
	int	j;

	j = 0;
	if (input[0] == input[1] || (input[0] == '<'
			&& input[1] == '>'))
	{
		(*i)++;
		j++;
	}
	token_tab[*nb]->str = ft_substr(input, 0, j + 1);
	(*i)++;
}
