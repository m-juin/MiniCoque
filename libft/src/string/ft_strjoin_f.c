/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:59:42 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/06 15:49:37 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strjoin_f(char *s1, char *s2, int to_free)
{
	char		*new_s;
	size_t		s1_len;
	size_t		s2_len;
	size_t		lcat_size;

	if (s1 == 0 || s2 == 0)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_s = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!new_s)
		return (0);
	ft_strlcpy(new_s, s1, s1_len + 1);
	lcat_size = s1_len + s2_len + 1;
	ft_strlcat(new_s, s2, lcat_size);
	if (to_free == 0)
	{
		free(s1);
		free(s2);
	}
	if (to_free == 1)
		free(s1);
	if (to_free == 2)
		free(s2);
	return (new_s);
}
