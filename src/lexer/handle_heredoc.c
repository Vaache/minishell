/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 22:33:39 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/16 17:56:41 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_heredoc(t_pars **pars, char *line, int i, int start);
void	handle_heredoc_input(char *string, t_pars **pars);

int	handle_heredoc(t_pars **pars, char *line, int i, int start)
{
	char	*limiter;
	char	*nil;
	int		first;
	int		end;
	int		k;

	nil = NULL;
	handle_space(pars, line, i, start);
	if (is_delim(*pars))
	{
		nil = "(NULL)";
		lstback(pars, lstadd(nil, WORD, 0, 1));	
	}
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
			k = check_redir(limiter, 0, 0);
			if (k == 1)
				break ;
			return (0);
		}
	}
	if (limiter)
	{
		handle_heredoc_input(limiter, pars);
		free(limiter);
		return (end + 1);
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
		lstback(pars, lstadd("", WORD, 0, 1));
	else
		lstback(pars, lstadd(res, WORD, 0, 1));
	free(res);
}
