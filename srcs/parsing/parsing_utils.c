/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:57:31 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/24 14:24:46 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

int	typify(int c)
{
	if (c == ' ' || c == '	')
		return (BLANK);
	else if (c == '|')
		return (PIPE);
	else if (c == '$')
		return (DOLLAR);
	else if (c == '<' || c == '>')
		return (REDIRECT);
	else if (c == '\'')
		return (S_QUOTE);
	else if (c == '\"')
		return (D_QUOTE);
	else if (c == '\0')
		return (NUULL);
	return (LITERAL);
}

int	digit_str(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
