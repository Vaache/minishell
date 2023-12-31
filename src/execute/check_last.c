/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_last.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:03:12 by vhovhann          #+#    #+#             */
/*   Updated: 2023/12/04 18:26:44 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_lasts(t_shell *main, t_tok *stack, int mode);
void static	check_last_redir(t_shell *main, t_tok *stack);
void static	check_last_input(t_shell *main, t_tok *stack);
void static	check_last_hd(t_shell *main, t_tok *stack);

int	check_lasts(t_shell *main, t_tok *stack, int mode)
{
	if (mode == 1)
	{
		main->last_hdoc = -42;
		main->last_redir = -42;
		main->last_input = -42;
		return (1);
	}
	check_last_hd(main, stack);
	check_last_redir(main, stack);
	check_last_input(main, stack);
	return (1);
}

void static	check_last_hd(t_shell *main, t_tok *stack)
{
	if (main->last_hdoc < 0)
		stack->last_hdoc = 1;
	main->last_hdoc = 1;
}

void static	check_last_redir(t_shell *main, t_tok *stack)
{
	if (main->last_redir < 0)
		stack->last_red = 1;
	main->last_redir = 1;
}

void static	check_last_input(t_shell *main, t_tok *stack)
{
	if (main->last_input < 0)
		stack->last_input = 1;
	main->last_input = 1;
}
