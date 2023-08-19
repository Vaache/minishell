/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_delims.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:59:24 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/19 14:32:48 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_xor(t_pars **pars, char *line, int i, int start);
int	handle_xand(t_pars **pars, char *line, int i, int start);
int	handle_pipe(t_pars **pars, char *line, int i, int start);

int	handle_xor(t_pars **pars, char *line, int i, int start)
{
	handle_space(pars, line, i, start);
	if (!(*pars))
		return (parse_error(2, "`||'", -1));
	lstback(pars, lstadd("||", XOR, 2, 1));
	return (i + 2);
}

int	handle_xand(t_pars **pars, char *line, int i, int start)
{
	
	handle_space(pars, line, i, start);
	if (!(*pars))
		return (parse_error(2, "`&&'", -1));
	lstback(pars, lstadd("&&", XAND, 2, 1));
	return (i + 2);
}

int	handle_pipe(t_pars **pars, char *line, int i, int start)
{
	
	handle_space(pars, line, i, start);
	if (!(*pars))
		return (parse_error(2, "`|'", -1));
	lstback(pars, lstadd("|", PIPE, 3, 1));
	return (i + 1);
}
