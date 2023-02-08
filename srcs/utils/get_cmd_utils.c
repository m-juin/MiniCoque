/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:06:37 by mjuin             #+#    #+#             */
/*   Updated: 2023/02/08 12:48:55 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static char	**get_splitted_envp(char *const *envp)
{
	int		i;
	char	**splitted_envp;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	splitted_envp = ft_split(envp[i] + 5, ':');
	return (splitted_envp);
}

static char	**get_paths(char *const *envp)
{
	int		i;
	char	**paths;
	char	**splitted_envp;

	splitted_envp = get_splitted_envp(envp);
	if (!splitted_envp)
		return (NULL);
	paths = malloc((strtab_len(splitted_envp) + 1) * sizeof(char *));
	if (!paths)
	{
		d_tab_free(splitted_envp);
		return (NULL);
	}
	i = 0;
	while (splitted_envp[i])
	{
		paths[i] = ft_strjoin_f(splitted_envp[i], "/", 1);
		i++;
	}
	paths[i] = 0;
	free(splitted_envp);
	return (paths);
}

char	*get_cmds(char *av, char *const *envp)
{
	char	**paths;
	char	*cmd;
	int		i;

	paths = get_paths(envp);
	d_tab_free((char **)envp);
	i = 0;
	while (paths[i])
	{
		cmd = ft_strjoin(paths[i], av);
		if (access(cmd, X_OK) == 0)
		{
			d_tab_free(paths);
			return (cmd);
		}
		free(cmd);
		i++;
	}
	d_tab_free(paths);
	cmd = ft_strdup(av);
	return (cmd);
}

static void	tokenarr_cpy(t_token **src, char **dst, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i] != NULL && j < size)
	{
		if (src[i]->str && src[i]->token_type != REDIRECT)
		{
			dst[j] = strndup(src[i]->str, -1);
			j++;
		}
		i++;
	}
	dst[j] = NULL;
}

char	**token_to_array(t_token **token)
{
	char	**array;
	size_t	size;
	size_t	pos;

	size = 0;
	pos = 0;
	if (token == NULL)
		return (NULL);
	size = token_tab_len(token, 1);
	array = malloc((size + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	tokenarr_cpy(token, array, size);
	return (array);
}
