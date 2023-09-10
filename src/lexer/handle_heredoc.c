/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 22:33:39 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/10 10:15:40 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_heredoc(t_tok **pars, char *line, int i, int start);
int		read_heredoc_input(t_main *main, t_tok *tok, char *line, t_env *env);
void	write_in_fd(char **res, int fd, t_env *env);
int		read_heredoc_input_2(char *line, char **res, t_tok *tok);

int	handle_heredoc(t_tok **pars, char *line, int i, int start)
{
	handle_space(pars, line, i, start);
	if (is_delim(*pars))
		lstback(pars, lstadd("(NULL)", WORD, 0, 1));
	lstback(pars, lstadd("<<", HEREDOC, 4, 1));
	return (i + 1);
}

int	read_heredoc_input(t_main *main, t_tok *tok, char *line, t_env *env)
{
	char	*res;

	res = NULL;
	tok->hdoc_fname = ft_strdup(main->hd->matrix[++main->hd->i]);
	tok->fd = open(tok->hdoc_fname, O_RDWR | O_CREAT | O_TRUNC, 0655);
	run_signals(4);
	while (1)
	{
		if (g_exit_status_ == 130)
		{
			free(res);
			return (130);
		}
		if (!read_heredoc_input_2(line, &res, tok))
			break ;
	}
	write_in_fd(&res, tok->fd, env);
	return (0);
}

int	read_heredoc_input_2(char *line, char **res, t_tok *tok)
{
	line = readline("> ");
	if (!line || ft_strcmp(line, tok->next->cmd) == 0)
	{
		free(line);
		return (0);
	}
	if (!(*res))
		(*res) = ft_strdup(line);
	else
		(*res) = strjoin_mode((*res), line, 1);
	free(line);
	return (1);
}

void	write_in_fd(char **res, int fd, t_env *env)
{
	t_exp	exp;
	char	*str;

	exp.i = -1;
	exp.l = 0;
	exp.str = NULL;
	exp.s = NULL;
	str = NULL;
	if (res)
		(*res) = ft_strjoin((*res), "\n", 1);
	else
		(*res) = ft_strdup("");
	if (ft_strchr((*res), '$'))
	{
		str = ft_strdup(expand((*res), &env, &exp));
		free((*res));
		(*res) = ft_strdup(str);
		free(str);
	}
	write(fd, (*res), ft_strlen((*res)));
	_close2_(fd, free_of_n((*res), NULL, NULL, -1) - 42);
	destroy_exp(&exp);
}
