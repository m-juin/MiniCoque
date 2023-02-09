/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_parsing_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:13:38 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/09 16:58:28 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

char	*get_quoted_var(char *input, int *i, int *start, t_env_var *env)
{
	char		*s;
	char		*tmp;
	int			start_param;
	t_env_var	*var;

	if (!input || !env)
		return (NULL);
	s = ft_substr(input, *start, *i - *start);
	if (!s)
		return (NULL);
	(*i)++;
	start_param = *i;
	while (input[*i] && (typify(input[*i]) != BLANK && input[*i] != '|'
			&& input[*i] != '\"' && input[*i] != '\''
			&& input[*i] != '$'))
		(*i)++;
	tmp = ft_substr(input, start_param, *i - start_param);
	var = get_env(env, tmp);
	free(tmp);
	if (var)
		s = ft_strjoin_f(s, var->value, 1);
	*start = *i;
	return (s);
}

char	*finish_double_q(char *s, char *input, int *i, int start)
{
	if (!s)
		s = ft_substr(input, start, *i - start);
	else
	{
		if (s[0] != '\0')
			s = ft_strjoin_f(s, ft_substr(input, start, *i - start), 0);
		else
			s = ft_strjoin_f(s, ft_substr(input, start, *i - start), 2);
	}
	return (s);
}
