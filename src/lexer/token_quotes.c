/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 21:22:01 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/06 16:00:03 by vhovhann         ###   ########.fr       */
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
		lstback(pars, lstadd(ft_substr(line, i + 1, count - i - 1), DQUOTE, 0, 2));
	else if (line[count] == '"' && i > 1 && line[count - 1] == ' ')
		lstback(pars, lstadd(ft_substr(line, i + 1, count - i - 1), DQUOTE, 0, 1));
	else if (line[count] == '"')
		lstback(pars, lstadd(ft_substr(line, i + 1, count - i - 1), DQUOTE, 0, 0));
	else
	{
		ft_printf(2, "Minishell : Syntax Error Duble Qoutes `\"\'\n");
		exit('\"' % 256);
	}
	return (count - 1);
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
		lstback(pars, lstadd(ft_substr(line, i + 1, count - i - 1), DQUOTE, 0, 2));
	else if (line[count] == '\'' && i > 1 && line[count - 1] == ' ')
		lstback(pars, lstadd(ft_substr(line, i + 1, count - i - 1), DQUOTE, 0, 1));
	else if (line[count] == '\'')
		lstback(pars, lstadd(ft_substr(line, i + 1, count - i - 1), DQUOTE, 0, 0));
	else
	{
		ft_printf(2, "Minishell : Syntax Error Single Qoutes `\'\'\n");
		exit('\'' % 256);
	}
	return (count - 1);
}