/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:29:30 by mjuin             #+#    #+#             */
/*   Updated: 2023/02/09 15:50:38 by mjuin            ###   ########.fr       */
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
	ft_close_fd(g_heredoc_data->fds[0], FALSE);
	ft_close_fd(g_heredoc_data->fds[1], FALSE);
	free_token(g_heredoc_data->tokentab);
	free(g_heredoc_data->limiter);
	free(g_heredoc_data->hdoc_path);
	ft_putstr_fd("\n", 1);
	free(g_heredoc_data);
	exit(130);
}
