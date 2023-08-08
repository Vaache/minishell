/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:55:09 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/08 20:55:11 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_append(t_pars **pars, char *line, int i, int start);
int	handle_trunc(t_pars **pars, char *line, int i, int start);
int	handle_infile(t_pars **pars, char *line, int i, int start);

int	handle_append(t_pars **pars, char *line, int i, int start)
{
	int	k;

	k = 1;
	if (!ft_isspace(line, start, i) && is_delim(*pars))
		lstback(pars, lstadd(ft_substr(line, start, i - start), WORD, 0, 1));
	else if (!ft_isspace(line, start, i))
		lstback(pars, lstadd(ft_substr(line, start, i - start), WORD, 0, 0));
	if (is_delim(*pars))
		lstback(pars, lstadd(NULL, WORD, 0, 1));
	lstback(pars, lstadd(">>", WRITE_APPEND, 4, 1));
	while (line[i + ++k])
	{
		if (line[i + k] != ' ')
		{
			if (ft_strncmp(&line[i + k], "&", 1) == 0 || \
				ft_strncmp(&line[i + k], "|", 1) == 0 || \
				ft_strncmp(&line[i + k], ">", 1) == 0)
				return (parse_error(2, ft_substr(&line[i + k], 0, 2)));
			if (ft_strcmp(&line[i + k], ">") == 0 || \
				ft_strcmp(&line[i + k], "<") == 0)
				return (parse_error(2, ft_substr(&line[i + k], 0, 1)));
			return (i + 2);
		}
	}
	return (parse_error(2, "newline"));
}

int	handle_trunc(t_pars **pars, char *line, int i, int start)
{
	int	k;

	if (!ft_isspace(line, start, i) && is_delim(*pars))
		lstback(pars, lstadd(ft_substr(line, start, i - start), WORD, 0, 1));
	else if (!ft_isspace(line, start, i))
		lstback(pars, lstadd(ft_substr(line, start, i - start), WORD, 0, 0));
	if (is_delim(*pars))
		lstback(pars, lstadd(NULL, WORD, 0, 1));
	lstback(pars, lstadd(">", WRITE_TRUNC, 4, 1));
	k = 0;
	while (line[i + ++k])
	{
		if (line[i + k] != ' ')
		{	
			if (ft_strncmp(&line[i + k], "&", 1) == 0 || \
				ft_strncmp(&line[i + k], "|", 1) == 0 || \
				ft_strncmp(&line[i + k], ">", 1) == 0)
				return (parse_error(2, ft_substr(&line[i + k], 0, 2)));
			if (ft_strcmp(&line[i + k], ">") == 0 || \
				ft_strcmp(&line[i + k], "<") == 0)
				return (parse_error(2, ft_substr(&line[i + k], 0, 1)));
			return (i + 1);
		}
	}
	return (parse_error(2, ">"));
}

int	handle_infile(t_pars **pars, char *line, int i, int start)
{
	int	k;

	if (!ft_isspace(line, start, i) && is_delim(*pars))
		lstback(pars, lstadd(ft_substr(line, start, i - start), WORD, 0, 1));
	else if (!ft_isspace(line, start, i))
		lstback(pars, lstadd(ft_substr(line, start, i - start), WORD, 0, 0));
	if (is_delim(*pars))
		lstback(pars, lstadd(NULL, WORD, 0, 1));
	lstback(pars, lstadd("<", INPUT, 4, 1));
	k = 0;
	while (line[i + ++k])
	{
		if (line[i + k] != ' ')
		{
			if (ft_strncmp(&line[i + k], "&", 1) == 0 || \
				ft_strncmp(&line[i + k], "|", 1) == 0 || \
				ft_strncmp(&line[i + k], ">", 1) == 0)
				return (parse_error(2, ft_substr(&line[i + k], 0, 2)));
			if (ft_strcmp(&line[i + k], ">") == 0 || \
				ft_strcmp(&line[i + k], "<") == 0)
				return (parse_error(2, ft_substr(&line[i + k], 0, 1)));
			return (i + 1);
		}
	}
	return (parse_error(2, "<"));
}
