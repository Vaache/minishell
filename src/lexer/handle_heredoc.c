/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 22:33:39 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/22 20:55:44 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_heredoc(t_pars **pars, char *line, int i, int start);
void	handle_heredoc_input(char *string, t_pars **pars);

int	handle_heredoc(t_pars **pars, char *line, int i, int start)
{
	char	*limiter;
	// char	*nil;
	int		counter;
	int		end;

	// nil = NULL;
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
	if (limiter)
	{
		handle_heredoc_input(limiter, pars);
		free(limiter);
		return (end - 1);
	}
	return (parse_error(2, "newline", -1));
}

void	handle_heredoc_input(char *string, t_pars **pars)
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
		else
		{
			if (res)
				res = ft_strjoin(res, "\n", 1);
			res = ft_strjoin(res, line, 1);
		}
		free(line);
	}
	if (!res)
	{
		res = ft_strdup("(NULL)\n");
		lstback(pars, lstadd(res, WORD, 0, 1));
	}
	else
	{
		res = ft_strjoin(res, "\n", 1);
		lstback(pars, lstadd(res, WORD, 0, 1));
	}
	free(res);
}
