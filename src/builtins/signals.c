/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:02:45 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/07 20:31:52 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int sig);
void	sig_handler_hdoc(int sig);
void	sig_handler_proc(int sig);

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status_ = sig + 128;
	}
	else if (sig == SIGQUIT)
		return ;
}

void	sig_handler_proc(int sig)
{
	if (sig == SIGINT)
		exit(128 + sig);
	else if (sig == SIGQUIT)
	{
		write(1, "Quit\n", 5);
		exit (128 + sig);
	}
}

void	sig_handler_hdoc(int sig)
{
	(void)sig;
	g_exit_status_ = 130;
	write(1, "\n", 1);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	call_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, &sig_handler);
}
