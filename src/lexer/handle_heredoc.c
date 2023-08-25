/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 22:33:39 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/25 20:15:49 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_heredoc(t_pars **pars, char *line, int i, int start);
char	*handle_heredoc_input(char *string);

int	handle_heredoc(t_pars **pars, char *line, int i, int start)
{
	char	*limiter;
	char	*res;
	int		counter;
	int		end;

	res = NULL;
	handle_space(pars, line, i, start);
	if (is_delim(*pars))
		lstback(pars, lstadd("(NULL)", WORD, 0, 1));
	lstback(pars, lstadd("<<", HEREDOC, 4, 1));
	counter = i + 2;
	limiter = NULL;
	while (line[counter] && line[counter] == ' ')
		counter++;
	end = find_limiter_end(line, i, counter);
	if (end == 0)
		return (0);
	limiter = ft_substr(line, counter, end - counter);
	if (!ft_strchr(limiter, '\'') || !ft_strchr(limiter, '"'))
		limiter = rem_quotes_lim(limiter);
	if (limiter)
	{
		lstback(pars, lstadd(limiter, WORD, 0, 1));
		free(limiter);
		return (end - 1);
	}
	return (parse_error(2, "newline", -1));
}

char	*handle_heredoc_input(char *string)
{
	char	*line;
	char	*res;

	line = NULL;
	res = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, string) == 0)
		{
			free(line);
			break ;
		}
		if (!res)
			res = ft_strdup(line);
		else
			res = strjoin_mode(res, line, 1);
		free(line);
	}
	if (!res)
		ft_strdup("");
	else
		res = ft_strjoin(res, "\n", 1);
	return (res);
}
