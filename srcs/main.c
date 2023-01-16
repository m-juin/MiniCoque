/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:23:07 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/16 17:15:02 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

void signalhandler(int  sig)
{
	if (sig == SIGQUIT)
		exit(0) ;
	sig = sig - 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(void)
{
	char *readed;
	char **splitted;
	
	signal(SIGINT, signalhandler);
	signal(SIGQUIT, signalhandler);
	while (1)
	{
		readed = readline("Minicoque > ");
		splitted = ft_split(readed, ' ');
		if (ft_strcmp(splitted[0], "exit") == 0)
			ft_exit(0);
		if (splitted != NULL && ft_strcmp(splitted[0], "echo") == 0)
		{
			add_history(readed);
			echo(splitted);
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