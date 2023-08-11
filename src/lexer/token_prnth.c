/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_prnth.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 18:48:35 by rmkrtchy          #+#    #+#             */
/*   Updated: 2023/08/10 18:39:03 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_oprnth(t_pars **pars, char *line, int i, int start)
{
	int		prnth;
	int		count;

	prnth = 1;
	if (!ft_isspace(line, start, i) && is_delim(*pars))
		lstback(pars, lstadd(ft_substr(line, start, i - start), WORD, 0, 1));
	else if (!ft_isspace(line, start, i))
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
		return (parse_error(2, "(", -1));
}

int	handle_clprnth(t_pars **pars, char *line, int i, int start)
{
	char	*tmp;

	tmp = NULL;
	if (!ft_isspace(line, start, i) && is_delim(*pars))
	{
		tmp = ft_substr(line, start, i - start);
		lstback(pars, lstadd(tmp, WORD, 0, 1));
	}
	else if (!ft_isspace(line, start, i))
	{
		tmp = ft_substr(line, start, i - start);
		lstback(pars, lstadd(tmp, WORD, 0, 0));
	}
	lstback(pars, lstadd(")", SUBSH_CLOSE, 1, 0));
	free(tmp);
	return (i + 1);
}
