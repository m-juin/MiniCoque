/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:29:30 by mjuin             #+#    #+#             */
/*   Updated: 2023/02/10 10:06:53 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minicoque.h>

t_heredoc	*g_heredoc_data = NULL;

void	signalhandler(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_printf_fd(2, "Quit (core dumped)\n");
		last_exit(FALSE, 131);
		return ;
	}
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	last_exit(FALSE, 130);
}

void	hsighandler(int sig)
{
	sig = sig - 1;
	ft_putstr_fd("\n", 1);
	close(0);
}
