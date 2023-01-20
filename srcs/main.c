/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:23:07 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/20 17:05:56 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

void	signalhandler(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_printf_fd(2, "Quit (core dumped)\n");
		return ;
	}
	printf("\n");
	rl_replace_line("", 0);
	rl_redisplay();
}

t_minicoque	*init(char **envp)
{
	t_minicoque	*data;
	int			pos;

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

static char	*get_prompt(void)
{
	char	*prompt;
	char	*path;
	size_t	pos;

	path = malloc(PATH_MAX * sizeof(char));
	getcwd(path, PATH_MAX);
	pos = ft_strlen(path);
	while (pos >= 0 && path[pos] != '/')
		pos--;
	prompt = ft_str_mega_join("%s%s > %s", PCOLOR, &path[pos + 1], RESET);
	free(path);
	return (prompt);
}

void	print_array(char * const *array)
{
	int	pos;

	pos = 0;
	while (array[pos] != NULL)
	{
		printf("%s\n", array[pos]);
		pos++;
	}
}

size_t	strtab_len(char **str_tab)
{
	int	i;

	i = 0;
	while (str_tab[i])
		i++;
	return (i);
}

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
		//free_tab(splitted_envp);
		return (NULL);
	}
	i = 0;
	while (splitted_envp[i])
	{
		paths[i] = ft_strjoin(splitted_envp[i], "/");
		i++;
	}
	paths[i] = 0;
	//free_tab(splitted_envp);
	return (paths);
}

static char	*get_cmds(char *av, char *const *envp)
{
	char	**paths;
	char	*cmd;
	int		i;

	paths = get_paths(envp);
	i = 0;
	while (paths[i])
	{
		cmd = ft_strjoin(paths[i], av);
		if (access(cmd, X_OK) == 0)
		{
			//free_tab(paths);
			return (cmd);
		}
		free(cmd);
		i++;
	}
	//free_tab(paths);
	return (NULL);
}

void	ft_exec(char **splitted, t_env_var *env)
{
	pid_t	pid;
	int		status;
	
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		execve(get_cmds(splitted[0], env_to_array(env)), splitted, env_to_array(env));
	}
	else
		waitpid(pid, &status, 0);
}

char **token_to_array(t_token **token)
{
	char	**array;
	size_t	size;
	size_t	pos;

	size = 0;
	if (token == NULL)
		return (NULL);
	while (token[size] != NULL)
		size++;
	if (size == 0)
		return (NULL);
	array = malloc((size + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	pos = 0;
	while (token[pos] != NULL)
	{
		array[pos] = strndup(token[pos]->str, -1);
		pos++;
	}
	array[pos] = NULL;
	return (array);
}

int	main(int ac, char **av, char **envp)
{
	char		*readed;
	char		**splitted;
	char		*prompt;
	t_minicoque	*coque_data;
	t_token		**token_input;

	ac = ac - 1;
	av[0] = 0;

	signal(SIGINT, signalhandler);
	coque_data = init(envp);
	while (1)
	{
		prompt = get_prompt();
		signal(SIGQUIT, SIG_IGN);
		readed = readline(prompt);
		if (readed == NULL)
			ft_exit(0);
		signal(SIGQUIT, signalhandler);
		if (ft_strcmp(readed, "") != 0)
			add_history(readed);
		token_input = lexer(readed, coque_data->env_var);
		splitted = token_to_array(token_input);
		if (splitted != NULL && splitted[0] != NULL)
		{
			if (ft_strcmp(splitted[0], "exit") == 0)
				ft_exit(splitted);
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
			else
				ft_exec(splitted, coque_data->env_var);
		}
		free(prompt);
	}
}
