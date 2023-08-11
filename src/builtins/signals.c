/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:02:45 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/10 14:39:17 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_stp(int sig);
void	call_signals(void);

void	handler_stp(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	call_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, &handler_stp);
	signal(SIGQUIT, &handler_stp);
}
