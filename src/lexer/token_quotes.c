/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 21:22:01 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/10 20:52:53 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_dquotes(t_tok **pars, char **line, int *i, int start);
int		handle_squotes(t_tok **pars, char **line, int *i, int start);
int		handle_quotes(t_tok **res, char **line, int *i, int count);

int	handle_dquotes(t_tok **pars, char **line, int *i, int start)
{
	int		count;
	char	*str;

	handle_space(pars, *line, *i, start);
	count = *i + 1;
	while ((*line)[count] && (*line)[count] != '"')
		count++;
	if ((*line)[*i] == '"')
		str = ft_substr(*line, *i + 1, count - *i - 1);
	else
		str = ft_substr(*line, *i, count - *i);
	if ((*line)[count] == '"' && (is_delim(*pars) || is_delim(*pars) == -1))
		lstback(pars, lstadd(str, DQUOTE, 0, 1));
	else if ((*line)[count] == '"' && *i > 1 && (*line)[*i - 1] == ' ')
		lstback(pars, lstadd(str, DQUOTE, 0, 2));
	else if ((*line)[count] == '"')
		lstback(pars, lstadd(str, DQUOTE, 0, 0));
	else
	{
		free(str);
		return (parse_error(2, "\"", -1) - 42);
	}
	free(str);
	*i = count;
	return (count);
}

int	handle_squotes(t_tok **pars, char **line, int *i, int start)
{
	int		count;
	char	*str;

	handle_space(pars, *line, *i, start);
	count = *i + 1;
	while ((*line)[count] && (*line)[count] != '\'')
		count++;
	str = ft_substr(*line, *i + 1, count - *i - 1);
	if ((*line)[count] == '\'' && (is_delim(*pars) || is_delim(*pars) == -1))
		lstback(pars, lstadd(str, SQUOTE, 0, 1));
	else if ((*line)[count] == '\'' && *i > 1 && (*line)[*i - 1] == ' ')
		lstback(pars, lstadd(str, SQUOTE, 0, 2));
	else if ((*line)[count] == '\'')
		lstback(pars, lstadd(str, SQUOTE, 0, 0));
	else
	{
		free(str);
		return (parse_error(2, "'", -1) - 42);
	}
	free(str);
	*i = count;
	return (count);
}

int	handle_quotes(t_tok **res, char **line, int *i, int count)
{
	int	status;

	if ((*line)[*i] == '\'')
	{
		status = handle_squotes(res, line, i, count);
		if (status < 0)
			return (status);
	}
	if ((*line)[*i] == '\"')
	{
		status = handle_dquotes(res, line, i, count);
		if (status < 0)
			return (status);
	}
	return (0);
}
