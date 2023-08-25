/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:45:00 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/25 20:24:40 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		find_limiter_end(char *line, int i, int start);
t_type	ttoa(char *token);
char	*token_is(t_type token);

char	*token_is(t_type token)
{
	if (token == DQUOTE)
		return ("\"");
	else if (token == SQUOTE)
		return ("'");
	else if (token == SUBSH_OPEN)
		return ("(");
	else if (token == SUBSH_CLOSE)
		return (")");
	else if (token == XOR)
		return ("||");
	else if (token == XAND)
		return ("&&");
	else if (token == PIPE)
		return ("|");
	else if (token == HEREDOC)
		return ("<<");
	else if (token == WRITE_APPEND)
		return (">>");
	else if (token == WRITE_TRUNC)
		return (">");
	else if (token == INPUT)
		return ("<");
	return ("AST");
}

t_type	ttoa(char *token)
{
	if (token[0] == '"')
		return (DQUOTE);
	else if (token[0] == '\'')
		return (SQUOTE);
	else if (token[0] == '(')
		return (SUBSH_OPEN);
	else if (token[0] == ')')
		return (SUBSH_CLOSE);
	else if (token[0] == '|' && token[1] == '|')
		return (XOR);
	else if (token[0] == '&' && token[1] == '&')
		return (XAND);
	else if (token[0] == '|')
		return (PIPE);
	else if (token[0] == '<' && token[1] == '<')
		return (HEREDOC);
	else if (token[0] == '>' && token[1] == '>')
		return (WRITE_APPEND);
	else if (token[0] == '>')
		return (WRITE_TRUNC);
	else if (token[0] == '<')
		return (INPUT);
	else if (token[0] == '\0')
		return (END);
	return (WORD);
}

int	find_limiter_end(char *line, int i, int start)
{
	int	end;

	end = start;
	while (line[end] && line[end] != ' ')
	{
		if (line[end] != '\0' && line[end] == '"')
			while (line[++end] != '\0' && line[end] != '"')
				;
		if (line[end] != '\0' && line[end] == '\'')
			while (line[++end] != '\0' && line[end] != '\'')
				;
		if (line[end] == '&' && line[end + 1] == '&')
			break ;
		else if (line[end] == '|' || line[end] == '<' || \
			line[end] == '>')
			break ;
		else if (line[end] == '(' || line[end] == ')')
			break ;
		if (line[end] != '\0')
		end++;
	}
	if (end == start)
	{
		if (line[i] == '\0')
			return (parse_error(2, "newline", 1));
		return (parse_error(2, (char *)token_is(ttoa(line + start)), 0));
	}
	return (end);
}

char	*rem_quotes_lim(char *limiter)
{
	int		i;
	int		qoute;
	char	*str;

	i = -1;
	qoute = 0;
	while (limiter && limiter[++i])
		if (limiter[i] == '"' || limiter[i] == '\'')
			qoute++;
	if (qoute % 2 != 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (i - qoute) + 1);
	if (!str)
		return (NULL);
	i = ((qoute = 0));
	while (limiter && limiter[i])
	{
		if (limiter[i] == '"' || limiter[i] == '\'')
			i++;
		else
			str[qoute++] = limiter[i++];
	}
	str[qoute] = '\0';
	return (str);
}
