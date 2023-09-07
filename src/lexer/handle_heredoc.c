/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 22:33:39 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/07 22:38:22 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_heredoc(t_tok **pars, char *line, int i, int start);
int		handle_heredoc_input(t_main *main, t_tok *tok, char *line);

int	handle_heredoc(t_tok **pars, char *line, int i, int start)
{
	char	*limiter;
	int		counter;
	int		end;

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
	if (ft_strchr(limiter, '\'') != 0 || ft_strchr(limiter, '"') != 0)
		limiter = rem_quotes_lim(limiter);
	if (limiter)
	{
		lstback(pars, lstadd(limiter, WORD, 0, 1));
		free(limiter);
		return (end - 1);
	}
	return (parse_error(2, "newline", -1));
}

int	handle_heredoc_input(t_main *main, t_tok *tok, char *line)
{
	char	*res;

	res = NULL;
	// signal(SIGINT, &sig_handler_hdoc);
	// signal(SIGQUIT, SIG_IGN);
	run_signals(4);
	tok->hdoc_fname = ft_strdup(main->hd->matrix[++main->hd->i]);
	tok->fd = open(tok->hdoc_fname, O_RDWR | O_CREAT | O_TRUNC, 0655);
	while (1)
	{
		if (g_exit_status_ == 130)
		{
			free(res);
			return (130);
		}
		line = readline("> ");
		if (!line || ft_strcmp(line, tok->next->cmd) == 0)
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
	if (res)
		res = ft_strjoin(res, "\n", 1);
	else
		res = ft_strdup("");
	write(tok->fd, res, ft_strlen(res));
	_close2_(tok->fd, free_of_n(res, NULL, NULL, -1) - 42);
	return (0);
}
