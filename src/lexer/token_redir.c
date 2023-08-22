/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:55:09 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/22 21:09:06 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_append(t_pars **pars, char *line, int i, int start);
int	handle_trunc(t_pars **pars, char *line, int i, int start);
int	handle_infile(t_pars **pars, char *line, int i, int start);

int	handle_append(t_pars **pars, char *line, int i, int start)
{
	int		k;

	handle_space(pars, line, i, start);
	if (is_delim(*pars))
		lstback(pars, lstadd("(NULL)", WORD, 0, 1));
	lstback(pars, lstadd(">>", WRITE_APPEND, 4, 1));
	k = 1;
	while (line[i + ++k])
	{
		if (line[i + k] != ' ' && (line[i + k] != '&' || line[i + k] != '|'))
			return (i + 1);
	}
	return (parse_error(2, "newline", -1));
}

int	handle_trunc(t_pars **pars, char *line, int i, int start)
{
	int		k;

	handle_space(pars, line, i, start);
	if (is_delim(*pars))
		lstback(pars, lstadd("(NULL)", WORD, 0, 1));
	lstback(pars, lstadd(">", WRITE_TRUNC, 4, 1));
	k = 0;
	while (line[i + ++k])
	{	
		if (line[i + k] != ' ')
			return (i);
	}
	return (parse_error(2, ">", -1));
}

int	handle_infile(t_pars **pars, char *line, int i, int start)
{
	int		k;

	handle_space(pars, line, i, start);
	if (is_delim(*pars))
		lstback(pars, lstadd("(NULL)", WORD, 0, 1));
	lstback(pars, lstadd("<", INPUT, 4, 1));
	k = 0;
	while (line[i + ++k])
	{
		if (line[i + k] != ' ')
			return (i);
	}
	return (parse_error(2, "newline", -1));
}
