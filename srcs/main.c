/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:23:07 by mjuin             #+#    #+#             */
/*   Updated: 2023/02/06 10:27:55 by gpasquet         ###   ########.fr       */
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

	data = malloc((1 * sizeof(t_minicoque)));
	if (data == NULL)
		return (NULL);
	data->env_var = NULL;
	data->curprocess = NULL;
	data->root = NULL;
	data->prompt = NULL;
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

int	main(int ac, char **av, char **envp)
{
	char		*readed;
	t_minicoque	*coque_data;
	t_token		**token_input;
	int			ret;

	ac = ac - 1;
	av[0] = 0;
	signal(SIGINT, signalhandler);
	coque_data = init(envp);
	while (1)
	{
		coque_data->prompt = get_prompt();
		signal(SIGQUIT, SIG_IGN);
		readed = readline(coque_data->prompt);
		if (readed == NULL)
			ft_exit(0, coque_data);
		signal(SIGQUIT, signalhandler);
		if (ft_strcmp(readed, "") != 0)
			add_history(readed);
		token_input = lexer(readed, coque_data->env_var);
		signal(SIGINT, SIG_IGN);
		ret = heredoc(token_input, coque_data);
		if (ret == -1)
		{
			token_input = free_token(token_input);
			token_input = NULL;
		}
		signal(SIGINT, signalhandler);
		coque_data->root = parsing(token_input, coque_data->env_var);
		if (coque_data->root != NULL)
			init_tree_exec(coque_data, coque_data->root);
	}
}
