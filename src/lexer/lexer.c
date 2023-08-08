/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 10:53:35 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/08 23:03:46 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		lexer(char *line, t_pars **pars);
void	lex(char *line, t_main *main);

int	lexer(char *line, t_pars **pars)
{
	int	start;
	int	i;
	int	l;
	int	subsh;

	i = 0;
	l = -1;
	subsh = 0;
	while (line && line[i])
	{
		start = i;
		while (line[i])
		{
			if (line[i] == '"')
				l = handle_dquotes(pars, line, i, start);
			else if (line[i] == '\'')
				l = handle_squotes(pars, line, i, start);
			else if (line[i] == '|' && line[i + 1] == '|')
				l = handle_xor(pars, line, i, start);
			else if (line[i] == '&' && line[i + 1] == '&')
				l = handle_xand(pars, line, i, start);
			else if (line[i] == ')')
			{
				if (subsh)
				{
					l = handle_clprnth(pars, line, i, start);
					subsh--;
				}
				else
					l = parse_error(2, "Minishell : Syntax Error `)'\n");
			}
			else if (line[i] == '(')
			{
				if (handle_oprnth(pars, line, i, start))
				{
					subsh++;
					l = -1;
				}
				else
					l = 0;
			}
			else if (line[i] == '<' && line[i + 1] == '<')
				l = handle_heredoc(pars, line, i, start);
			else if (line[i] == '>' && line[i + 1] == '>')
				l = handle_append(pars, line, i, start);
			else if (line[i] == '>' && line[i + 1] != '>')
				l = handle_trunc(pars, line, i, start);
			else if (line[i] == '<' && line[i + 1] != '<')
				l = handle_infile(pars, line, i, start);
			else if (line[i] == '|')
				l = handle_pipe(pars, line, i, start);
			else if (ft_strchr(" \n\t\v\r\f", line[i]))
				handle_space(pars, line, i, start);
			else if (line[i + 1] == '\0')
				handle_space(pars, line, i + 1, start);
			else
			{
				i++;
				continue ;
			}
			if (l == 0)
				return (0);
			else if (l > 0)
			{
				i = l;
				l = -1;
			}
			break ;
		}
		if (line[i] == '\0')
			break ;
		i++;
	}
	lstback(pars, lstadd("AST", END, 1, 2));
	return (1);
}

void	lex(char *line, t_main *main)
{
	if (!lexer(line, &(main->lex)))
	{
		destroy_main(main);
		main->exit_status = 258;
		return ;
	}
	if (!check_valid(main))
	{
		destroy_main(main);
		main->exit_status = 258;
		return ;
	}
}
