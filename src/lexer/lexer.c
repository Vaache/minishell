/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 10:53:35 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/08 16:52:53 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		lexer(char *line, t_tok **pars);
int		lexer_2(t_tok ***pars, char *line, int i, int start);
void	lex(char *line, t_main *main, t_env **env);

int	lexer(char *line, t_tok **pars)
{
	int	start;
	int	i;
	int	subsh;

	i = 0;
	subsh = 0;
	while (line && line[i])
	{
		start = i;
		while (line[i])
		{
			if (line[i] == ')')
			{
				if (subsh)
				{
					i = handle_clprnth(pars, line, i, start);
					subsh--;
				}
				else
					i = parse_error(2, "Minishell : Syntax Error `)'\n", 0);
			}
			else if (line[i] == '(' && handle_oprnth(pars, line, i, start))
				subsh++;
			else if (check_for_lexer(line, i))
				i = lexer_2(&pars, line, i, start);
			else if (ft_strchr(" \n\t\v\r\f", line[i]))
				handle_space(pars, line, i, start);
			else if (line[i + 1] == '\0')
				handle_space(pars, line, i + 1, start);
			else
			{
				i++;
				continue ;
			}
			i++;
			break ;
		}
	}
	lstback(pars, lstadd("AST", END, 1, 2));
	return (1);
}

int	lexer_2(t_tok ***pars, char *line, int i, int start)
{
	if (line[i] == '"')
		i = handle_dquotes((*pars), line, i, start);
	else if (line[i] == '\'')
		i = handle_squotes((*pars), line, i, start);
	else if (line[i] == '|' && line[i + 1] == '|')
		i = handle_xor((*pars), line, i, start);
	else if (line[i] == '&' && line[i + 1] == '&')
		i = handle_xand((*pars), line, i, start);
	else if (line[i] == '<' && line[i + 1] == '<')
		i = handle_heredoc((*pars), line, i, start);
	else if (line[i] == '>' && line[i + 1] == '>')
		i = handle_append((*pars), line, i, start);
	else if (line[i] == '>' && line[i + 1] != '>')
		i = handle_trunc((*pars), line, i, start);
	else if (line[i] == '<' && line[i + 1] != '<')
		i = handle_infile((*pars), line, i, start);
	else if (line[i] == '|')
		i = handle_pipe((*pars), line, i, start);
	return (i);
}

void	lex(char *line, t_main *main, t_env **env)
{
	t_tok	*tmp;

	if (!lexer(line, &(main->lex)) || !check_valid(main))
	{
		destroy_main(main);
		g_exit_status_ = 258;
		handle_dollar(g_exit_status_, env);
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
	parsing(main, env);
}
