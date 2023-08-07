/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_delims.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmkrtchy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:59:24 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/07 20:18:22 by rmkrtchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handel_xor(t_pars **pars, char *line, int i, int start);
int	handel_xand(t_pars **pars, char *line, int i, int start);

int	handel_xor(t_pars **pars, char *line, int i, int start)
{
	if (!ft_isspace(line, i, start) && is_delim(*pars))
		lstback(pars, lstadd(ft_substr(line, start, i - start), WORD, 0, 1));
	else if (!ft_isspace(line, i, start))
		lstback(pars, lstadd(ft_substr(line, start, i - start), WORD, 0, 0));
	if (!(*pars))
		return (parse_error(2, "Minishell : Syntax Error XOR `||'\n"));
	lstback(pars, lstadd("||", XOR, 2, 1));
	return (i + 1);
}

int	handel_xand(t_pars **pars, char *line, int i, int start)
{
	if (!ft_isspace(line, i, start) && is_delim(*pars))
		lstback(pars,(lstadd(ft_substr(line, start, i - start), WORD, 0, 1)));
	else if (!ft_isspace(line, i, start))
		lstback(pars, lstadd(ft_substr(line, start, i - start), WORD, 0, 0));
	if (!(*pars))
		return (parse_error(2, "Minishell : Syntax Error XAND `&&'\n"));
	lstback(pars, lstadd("&&", XAND, 2, 1));
	return (i + 1);
}
