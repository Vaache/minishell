/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 21:22:01 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/15 17:17:40 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_dquotes(t_pars **pars, char *line, int i, int start);
int	handle_squotes(t_pars **pars, char *line, int i, int start);

int	handle_dquotes(t_pars **pars, char *line, int i, int start)
{
	int		count;
	char	*str;

	handle_space(pars, line, i, start);
	count = i + 1;
	while (line[count] && line[count] != '"')
		count++;
	str = ft_substr(line, i + 1, count - i - 1);
	if (line[count] == '"' && is_delim(*pars))
		lstback(pars, lstadd(str, DQUOTE, 0, 1));
	else if (line[count] == '"' && i > 1 && line[i - 1] == ' ')
		lstback(pars, lstadd(str, DQUOTE, 0, 2));
	else if (line[count] == '"')
		lstback(pars, lstadd(str, DQUOTE, 0, 0));
	else
	{
		free(str);
		return (parse_error(2, "Minishell : Syntax Error Duble Qoutes `\"\'", -1));
	}
	free(str);
	return (count);
}

int	handle_squotes(t_pars **pars, char *line, int i, int start)
{
	int		count;
	char	*str;

	handle_space(pars, line, i, start);
	count = i + 1;
	while (line[count] && line[count] != '\'')
		count++;
	str = ft_substr(line, i + 1, count - i - 1);
	if (line[count] == '\'' && is_delim(*pars))
		lstback(pars, lstadd(str, DQUOTE, 0, 1));
	else if (line[count] == '\'' && i > 1 && line[i - 1] == ' ')
		lstback(pars, lstadd(str, DQUOTE, 0, 2));
	else if (line[count] == '\'')
		lstback(pars, lstadd(str, DQUOTE, 0, 0));
	else
	{
		free(str);
		return (parse_error(2, "Minishell : Syntax Error Single Qoutes `\'\'", -1));
	}
	free(str);
	return (count);
}

//	0000 -> voch cmd a voch space uni
//	0001 -> space chuni cmd a
//	0010 -> space uni, cmd chi
//	0011 -> space uni, cmd a
//