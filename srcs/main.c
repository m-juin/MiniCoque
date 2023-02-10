/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:23:07 by mjuin             #+#    #+#             */
/*   Updated: 2023/02/10 10:06:29 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

static t_minicoque	*create_data(char **envp)
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
	replace_value(get_env(data->env_var, "_"), "_=]");
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

static t_btree	*parse(t_env_var *env, char *read)
{
	t_token	**token_input;
	int		ret;
	t_btree	*tree;

	token_input = lexer(read, env);
	signal(SIGINT, SIG_IGN);
	ret = heredoc(token_input);
	if (ret == -1)
	{
		token_input = free_token(token_input);
		token_input = NULL;
	}
	signal(SIGINT, signalhandler);
	tree = parsing(token_input, env);
	return (tree);
}

static t_minicoque	*init(int ac, char **envp)
{
	t_minicoque	*data;

	if (ac > 2)
	{
		ft_printf_fd(2, "Too much argument for minishell\n");
		return (NULL);
	}
	signal(SIGINT, signalhandler);
	data = create_data(envp);
	if (data == NULL)
	{
		ft_printf_fd(2, "Error on base data creation\n");
		return (NULL);
	}
	return (data);
}

int	main(int ac, char **av, char **envp)
{
	char		*readed;
	t_minicoque	*coque_data;

	(void)av;
	coque_data = init(ac, envp);
	if (coque_data == NULL)
		exit(1);
	while (1)
	{
		coque_data->prompt = get_prompt();
		signal(SIGQUIT, SIG_IGN);
		readed = readline(coque_data->prompt);
		s_free(coque_data->prompt);
		if (readed == NULL)
			ft_exit(0, coque_data);
		if (ft_strcmp(readed, "") != 0)
			add_history(readed);
		coque_data->root = parse(coque_data->env_var, readed);
		signal(SIGQUIT, signalhandler);
		if (coque_data->root != NULL)
			init_tree_exec(coque_data, coque_data->root);
	}
}
