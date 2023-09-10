/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 10:53:35 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/10 10:28:46 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_tokens_p1(t_tok **res, char **line, int *i, int counter);
void	lex(char **line, t_main *main, t_env *env);
int		lexer(t_tok **res, char **line);

int	handle_tokens_p1(t_tok **res, char **line, int *i, int counter)
{
	if ((*line)[*i] == ')')
		*i = handle_clprnth(res, *line, *i, counter);
	else if ((*line)[*i] == '(')
		*i = handle_oprnth(res, *line, *i, counter);
	else if ((*line)[*i] == '|' && (*line)[*i + 1] == '|')
		*i = handle_xor(res, *line, *i, counter);
	else if ((*line)[*i] == '&' && (*line)[*i + 1] == '&')
		*i = handle_xand(res, *line, *i, counter);
	else if ((*line)[*i] == '<' && (*line)[*i + 1] == '<')
		*i = handle_heredoc(res, *line, *i, counter);
	else if ((*line)[*i] == '>' && (*line)[*i + 1] == '>')
		*i = handle_append(res, *line, *i, counter);
	else if ((*line)[*i] == '>')
		*i = handle_trunc(res, *line, *i, counter);
	else if ((*line)[*i] == '<')
		*i = handle_infile(res, *line, *i, counter);
	else if ((*line)[*i] == '|')
		*i = handle_pipe(res, *line, *i, counter);
	else if (ft_strchr(" \n\t\v\r\f\0", (*line)[*i]))
		handle_space(res, *line, *i, counter);
	else if ((*line)[*i + 1] == '\0')
		handle_space(res, *line, *i + 1, counter);
	else
		return (0);
	return (1);
}

int	inner_while(t_tok **res, char **line, int *i, int counter)
{
	int	key;

	while ((*line)[*i])
	{
		if ((*line)[*i] == '"' || (*line)[*i] == '\'')
		{
			key = handle_quotes(res, line, i, counter);
			if (key)
				return (key);
		}
		else if (!handle_tokens_p1(res, line, i, counter))
		{
			(*i)++;
			continue ;
		}
		break ;
	}
	return (0);
}

int	lexer(t_tok **res, char **line)
{
	int		i;
	int		counter;

	i = 0;
	while (*line && (*line)[i])
	{
		counter = i;
		if (inner_while(res, line, &i, counter) == -42)
			return (0);
		i++;
	}
	lstback(res, lstadd("AST", END, 1, 2));
	return (1);
}

void	lex(char **line, t_main *main, t_env *env)
{
	t_tok	*tmp;

	if (!lexer(&(main->lex), line) || !check_valid(main) || !main->lex)
	{
		destroy_main(main);
		main->exit_status = 258;
		return ;
	}
	tmp = main->lex;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
			main->hdoc++;
		tmp = tmp->next;
	}
	if (main->hdoc > 15)
	{
		ft_printf(2, "Minishell: maximum here-document count exceeded");
		exit(2);
	}
	parsing(main, &env);
}
