/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:48:23 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/01 16:22:32 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

int	token_tab_len(t_token **tab, int redir)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (tab[i])
	{
		if (redir == 0)
			len++;
		else
		{
			if (tab[i]->token_type != REDIRECT)
				len++;
		}
		i++;
	}
	return (len);
}

void	free_token(t_token **token_tab)
{
	int		i;
	void	*tmp;

	i = 0;
	while (token_tab[i])
	{
		free(token_tab[i]->str);
		free(token_tab[i]);
		i++;
	}
	tmp = token_tab;
	token_tab = NULL;
	free(tmp);
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

void	pipe_token(t_token **token_tab, int *nb)
{
	token_tab[*nb]->str = ft_strdup("|");
	token_tab[*nb]->token_type = PIPE;
	(*nb)++;
}

void	redirect_token(t_token *token, char *input, int *i)
{
	int	start;

	start = *i;
	while (typify(input[*i]) == REDIRECT)
		(*i)++;
	while (typify(input[*i]) == BLANK)
		(*i)++;
	token->str = ft_substr(input, start, *i - start);
	token->token_type = REDIRECT;
}
