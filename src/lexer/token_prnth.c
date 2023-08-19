/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_prnth.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 18:48:35 by rmkrtchy          #+#    #+#             */
/*   Updated: 2023/08/19 14:32:34 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_oprnth(t_pars **pars, char *line, int i, int start)
{
	int		prnth;
	int		count;

	prnth = 1;
	handle_space(pars, line, i, start);
	lstback(pars, lstadd("(", SUBSH_OPEN, 1, 1));
	count = i;
	while (prnth && line[count])
	{
		count++;
		if (line[count] == '(')
			prnth++;
		else if (line[count] == ')')
			prnth--;
	}
	if (line[count] == ')')
		return (1);
	else
		return (parse_error(2, "(", -1));
}

int	handle_clprnth(t_pars **pars, char *line, int i, int start)
{
	handle_space(pars, line, i, start);
	if (lstlast(*pars)->type == SUBSH_OPEN)
		return (0 & parse_error(2, ")", 0));
	lstback(pars, lstadd(")", SUBSH_CLOSE, 1, 0));
	return (i + 1);
}
