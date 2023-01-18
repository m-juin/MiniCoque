/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:23:07 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/18 12:21:39 by gpasquet         ###   ########.fr       */
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

int	main(int ac, char **av, char **envp)
{
	char 		*readed;
	char		**splitted;
	t_minicoque	*coque_data;

	ac = ac - 1;
	av[0] = 0;

	signal(SIGINT, signalhandler);
	signal(SIGQUIT, signalhandler);
	coque_data = init(envp);
	while (1)
	{
		readed = readline("Minicoque > ");
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
		}
	}
}

/*int last_error(int get, int error)
{
	static int lasterror;

	if (get == 1)
		return (lasterror);
	else
		lasterror = error;
}*/
