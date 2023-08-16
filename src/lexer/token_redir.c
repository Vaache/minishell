/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:55:09 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/15 21:05:43 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_append(t_pars **pars, char *line, int i, int start);
int	handle_trunc(t_pars **pars, char *line, int i, int start);
int	handle_infile(t_pars **pars, char *line, int i, int start);
int	check_redir(char *line, int i, int k);

int	handle_append(t_pars **pars, char *line, int i, int start)
{
	int		k;
	char	*nil;

	k = 1;
	nil = NULL;
	handle_space(pars, line, i, start);
	if (is_delim(*pars))
	{
		nil = "(NULL)";
		lstback(pars, lstadd(nil, WORD, 0, 1));
	}
	lstback(pars, lstadd(">>", WRITE_APPEND, 4, 1));
	while (line[i + ++k])
	{
		if (line[i + k] != ' ')
		{
			if (check_redir(line, i, k) == 1)
				return (i + 2);
			return (0);
		}
	}
	return (parse_error(2, "newline", -1));
}

int	handle_trunc(t_pars **pars, char *line, int i, int start)
{
	int		k;
	char	*nil;

	nil = NULL;
	handle_space(pars, line, i, start);
	if (is_delim(*pars))
	{
		nil = "(NULL)";
		lstback(pars, lstadd(nil, WORD, 0, 1));
	}
	lstback(pars, lstadd(">", WRITE_TRUNC, 4, 1));
	k = 0;
	while (line[i + ++k])
	{	
		if (line[i + k] != ' ')
		{
			if (check_redir(line, i, k) == 1)
				return (i + 1);
			return (0);
		}
	}
	return (parse_error(2, ">", -1));
}

int	handle_infile(t_pars **pars, char *line, int i, int start)
{
	int		k;
	char	*nil;

	nil = NULL;
	handle_space(pars, line, i, start);
	if (is_delim(*pars))
	{
		nil = "(NULL)";
		lstback(pars, lstadd(nil, WORD, 0, 1));
	}
	lstback(pars, lstadd("<", INPUT, 4, 1));
	k = 0;
	while (line[i + ++k])
	{
		if (line[i + k] != ' ')
		{
			if (check_redir(line, i, k) == 1)
				return (i + 1);
			return (0);
		}
	}
	return (parse_error(2, "<", -1));
}

int	check_redir(char *line, int i, int k) 
{
	char	*str;
	
	str = search_redir(&line[i + k]);
	if (str != NULL)
		return (parse_error(2, str, 1));
	free(str);
	return (1);
}