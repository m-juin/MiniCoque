/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:23:07 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/25 13:19:20 by gpasquet         ###   ########.fr       */
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

int	main(int ac, char **av, char **envp)
{
	char		*readed;
	char		*prompt;
	t_minicoque	*coque_data;
	t_token		**token_input;
	t_btree		*parsed_tree;

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
		{
			s_free(prompt);
			ft_exit(0, coque_data);
		}
		signal(SIGQUIT, signalhandler);
		if (ft_strcmp(readed, "") != 0)
			add_history(readed);
		token_input = lexer(readed, coque_data->env_var);
		parsed_tree = parsing(token_input, coque_data->env_var);
		if (parsed_tree != NULL)
			init_tree_exec(coque_data, parsed_tree);
		s_free(prompt);
	}
}
