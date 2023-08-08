/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 22:33:39 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/08 20:42:40 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_heredoc(t_pars **pars, char *line, int i, int start);
void	handle_heredoc_input(char *string, t_pars **pars);

int	handle_heredoc(t_pars **pars, char *line, int i, int start)
{
	char	*limiter;
	int		first;
	int		end;
	int		k;

	if (!ft_isspace(line, start, i) && is_delim(*pars))
		lstback(pars, lstadd(ft_substr(line, start, i - start), WORD, 0, 1));
	else if (!ft_isspace(line, start, i))
		lstback(pars, lstadd(ft_substr(line, start, i - start), WORD, 0, 0));
	if (is_delim(*pars))
		lstback(pars, lstadd(NULL, WORD, 0, 1));
	lstback(pars, lstadd("<<", HEREDOC, 4, 1));
	k = 1;
	first = 0;
	limiter = NULL;
	while (line[i + ++k])
	{
		if (!first && line[i + k] != ' ')
			first = i + k;
		if (first && (line[i + k + 1] == '\0' || line[i + k + 1] == ' '))
		{
			end = i + k;
			limiter = ft_substr(line, first, end - first + 1);
			if (ft_strncmp(limiter, "&", 1) == 0 || \
				ft_strncmp(limiter, "|", 1) == 0 || \
				ft_strncmp(limiter, ">", 1) == 0)
				return (parse_error(2, ft_substr(limiter, 0, 2)));
			if (ft_strcmp(limiter, ">") == 0 || ft_strcmp(limiter, "<") == 0)
				return (parse_error(2, ft_substr(limiter, 0, 1)));
			break ;
		}
	}
	if (limiter)
	{
		handle_heredoc_input(limiter, pars);
		return (end);
	}
	return (parse_error(2, "newline"));
}

void	handle_heredoc_input(char *string, t_pars **pars)
{
	char	*line;
	char	*res;

	line = NULL;
	res = NULL;
	while (1)
	{
		line = readline(">");
		if (!line)
			return ;
		if (ft_strcmp(string, line) == 0)
			break ;
		else
			res = ft_strjoin(res, line, 1);
		free(line);
	}
	lstback(pars, lstadd(res, WORD, 0, 1));
	free(string);
	free(res);
}
