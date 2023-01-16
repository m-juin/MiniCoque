/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:23:07 by mjuin             #+#    #+#             */
/*   Updated: 2023/01/16 12:08:47 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

void signalhandler(int  sig)
{
	if (sig == SIGQUIT)
		exit(0);
	sig = sig - 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(void)
{
	char *readed;
	signal(SIGINT, signalhandler);
	signal(SIGABRT, signalhandler);
	signal(SIGQUIT, signalhandler);
	while (1)
	{
		readed = readline("Minicoque > ");
		add_history(readed);
		printf("%s\n", readed);
	}
}

/*int set_last_error(int get, int error)
{
	static int lasterror;

	if (get == 1)
		return (lasterror);
	else
		lasterror = error;
}*/