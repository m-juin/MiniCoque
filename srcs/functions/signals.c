/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:29:30 by mjuin             #+#    #+#             */
/*   Updated: 2023/02/13 15:28:46 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

void	signalhandler(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_printf_fd(2, "Quit (core dumped)\n");
		g_exit_code = 131;
		return ;
	}
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_code = 130;
}

void	hsighandler(int sig)
{
	sig = sig - 1;
	ft_putstr_fd("\n", 1);
	close(0);
	g_exit_code = 130;
}

void	fsighandler(int sig)
{
	sig = sig - 1;
	ft_putstr_fd("\n", 1);
	g_exit_code = 130;
}
