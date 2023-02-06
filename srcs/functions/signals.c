/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:29:30 by mjuin             #+#    #+#             */
/*   Updated: 2023/02/06 11:31:45 by mjuin            ###   ########.fr       */
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

void	hsighandler(int sig)
{
	sig = sig - 1;
	ft_putstr_fd("\n", 1);
	exit(2);
}
