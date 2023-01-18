/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:23:07 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/18 17:22:07 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

void signalhandler(int  sig)
{
	if (sig == SIGQUIT)
		ft_exit(0) ;
	sig = sig - 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	get_env_size(t_env_var *env)
{
	size_t	size;

	size = 0;
	while (env != NULL)
	{
		size++;
		env = env->next;
	}
	return (size);
}

t_minicoque	*init(char **envp)
{
	t_minicoque	*data;
	int	pos;
	
	data = malloc(sizeof(data));
	if (data == NULL)
		return (NULL);
	data->env_var = NULL;
	pos = 0;
	while (envp[pos])
	{
		ft_env_add_back(&data->env_var, create_env(envp[pos]));
		pos++;
	}
	replace_value(get_env(data->env_var, "_"), "]");
	return (data);
}

static char	*get_prompt()
{
	char	*prompt;
	char	*path;
	char	*tmp;
	size_t	pos;

	path = malloc(PATH_MAX * sizeof(char));
	getcwd(path, PATH_MAX);
	pos = ft_strlen(path);
	prompt = strndup(PCOLOR, -1);
	while (pos >= 0 && path[pos] != '/')
		pos--;
	tmp = ft_strndup(&path[pos + 1], -1);
	prompt = ft_strjoin(prompt, tmp);
	free(tmp);
	prompt = ft_strjoin(prompt, " > ");
	prompt = ft_strjoin(prompt, RESET);
	free(path);
	return (prompt);
}

int	main(int ac, char **av, char **envp)
{
	char 		*readed;
	char		**splitted;
	char		*prompt;
	t_minicoque	*coque_data;

	ac = ac - 1;
	av[0] = 0;

	signal(SIGINT, signalhandler);
	signal(SIGQUIT, signalhandler);
	coque_data = init(envp);
	while (1)
	{
		prompt = get_prompt();
		readed = readline(prompt);
		lexer(readed, coque_data->env_var);
		splitted = ft_split(readed, ' ');
		if (splitted != NULL && splitted[0] != NULL)
		{
			add_history(readed);
			if (ft_strcmp(splitted[0], "exit") == 0)
				ft_exit(0);
			else if (ft_strcmp(splitted[0], "echo") == 0)
				echo(splitted);
			else if (ft_strcmp(splitted[0], "env") == 0)
				env(coque_data->env_var, splitted);
			else if (ft_strcmp(splitted[0], "export") == 0)
				export(coque_data->env_var, splitted);
			else if (ft_strcmp(splitted[0], "unset") == 0)
				unset(coque_data->env_var, splitted);
			else if (ft_strcmp(splitted[0], "pwd") == 0)
				pwd();
			else if (ft_strcmp(splitted[0], "cd") == 0)
				cd(coque_data->env_var, splitted);
		}
		free(prompt);
	}
}
