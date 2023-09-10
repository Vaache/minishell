/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_prnth.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 18:48:35 by rmkrtchy          #+#    #+#             */
/*   Updated: 2023/09/10 09:20:00 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_oprnth(t_tok **pars, char *line, int i, int start)
{
	handle_space(pars, line, i, start);
	lstback(pars, lstadd("(", SUBSH_OPEN, 1, 1));
	return (i);
}

int	handle_clprnth(t_tok **pars, char *line, int i, int start)
{
	handle_space(pars, line, i, start);
	lstback(pars, lstadd(")", SUBSH_CLOSE, 1, 0));
	return (i);
}
