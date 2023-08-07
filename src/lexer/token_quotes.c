/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmkrtchy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 21:22:01 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/07 18:35:05 by rmkrtchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handel_dquotes(t_pars **pars, char *line, int i, int start);
int	handel_squotes(t_pars **pars, char *line, int i, int start);

int	handel_dquotes(t_pars **pars, char *line, int i, int start)
{
	int	count;
	
	if (!ft_isspace(line, start, i) && is_delim(*pars))
		lstback(pars, lstadd(ft_substr(line, start, i - start), WORD, 0, 1));
	else if (!ft_isspace(line, start, i))
		lstback(pars, lstadd(ft_substr(line, start, i - start), WORD, 0, 0));
	count = i + 1;
	while (line[count] && line[count] != '"')
		count++;
	if (line[count] == '"' && is_delim(*pars))
		lstback(pars, lstadd(ft_substr(line, i + 1, count - i - 1), DQUOTE, 0, 1));
	else if (line[count] == '"' && i > 1 && line[count - 1] == ' ')
		lstback(pars, lstadd(ft_substr(line, i + 1, count - i - 1), DQUOTE, 0, 2));
	else if (line[count] == '"')
		lstback(pars, lstadd(ft_substr(line, i + 1, count - i - 1), DQUOTE, 0, 0));
	else
		return (parse_error(2, "Minishell : Syntax Error Duble Qoutes `\"\'\n"));
	return (count);
}

int	handel_squotes(t_pars **pars, char *line, int i, int start)
{
	int	count;
	
	if (!ft_isspace(line, start, i) && is_delim(*pars))
		lstback(pars, lstadd(ft_substr(line, start, i - start), WORD, 0, 1));
	else if (!ft_isspace(line, start, i))
		lstback(pars, lstadd(ft_substr(line, start, i - start), WORD, 0, 0));
	count = i + 1;
	while (line[count] && line[count] != '\'')
		count++;
	if (line[count] == '\'' && is_delim(*pars))
		lstback(pars, lstadd(ft_substr(line, i + 1, count - i - 1), DQUOTE, 0, 1));
	else if (line[count] == '\'' && i > 1 && line[count - 1] == ' ')
		lstback(pars, lstadd(ft_substr(line, i + 1, count - i - 1), DQUOTE, 0, 2));
	else if (line[count] == '\'')
		lstback(pars, lstadd(ft_substr(line, i + 1, count - i - 1), DQUOTE, 0, 0));
	else
		return (parse_error(2, "Minishell : Syntax Error Single Qoutes `\'\'\n"));
	return (count);
}


//	0000 -> voch cmd a voch space uni
//	0001 -> space chuni cmd a
//	0010 -> space uni, cmd chi
//	0011 -> space uni, cmd a
//