/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_prnth.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 18:48:35 by rmkrtchy          #+#    #+#             */
/*   Updated: 2023/08/08 16:18:15 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_oprnth(t_pars **pars, char *line, int i, int start)
{
	int	prnth;
	int	count;

	prnth = 1;
	if (!ft_isspace(line, i, start) && is_delim(*pars))
		lstback(pars, lstadd(ft_substr(line, start, i - start), WORD, 0, 1));
	else if (!ft_isspace(line, i, start))
		lstback(pars, lstadd(ft_substr(line, start, i - start), WORD, 0, 0));
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
		return (parse_error(2, "("));
}

int	handle_clprnth(t_pars **pars, char *line, int i, int start)
{
	if (!ft_isspace(line, i, start) && is_delim(*pars))
		lstback(pars, lstadd(ft_substr(line, start, i - start), WORD, 0, 1));
	else if (!ft_isspace(line, i, start))
		lstback(pars, lstadd(ft_substr(line, start, i - start), WORD, 0, 0));
	lstback(pars, lstadd(")", SUBSH_CLOSE, 1, 1));
	return (i + 1);
}
