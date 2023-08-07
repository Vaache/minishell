/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmkrtchy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 10:53:35 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/07 20:18:10 by rmkrtchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer(char *line, t_pars **pars);
void	lex(char *line, t_main *main);

int	lexer(char *line, t_pars **pars)
{
	int	start;
	int	i;
	int	l;
	int	subsh;

	i = -1;
	l = -1;
	subsh = 0;
	while (line && line[++i])
	{
		start = i;
		while (line[i])
		{
			if (line[i] == '"')
				l = handel_dquotes(pars, line, i, start);
			else if (line[i] == '\'')
				l = handel_squotes(pars, line, i, start);
			else if (line[i] == '|' && line[i + 1] == '|')
				l = handel_xor(pars, line, i, start);
			else if (line[i] == '&' && line[i + 1] == '&')
				l = handel_xand(pars, line, i, start);
			else if (line[i] == ')')
			{
				if (subsh)
				{
					l = handel_clprnth(pars, line, i, start);
					subsh--;
				}
				else
					parse_error(2, "Minishell : Syntax Error `)'\n");
			}
			else if(line[i] == '(')
			{
				if(handel_oprnth(pars, line, i, start))
				{
					subsh++;
					l = -1;
				}
				else
					l = 0;
			}
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
			break;
		}
	}
	// lstback(pars, lstadd("AST", END, 1, 2));
	return (1);
}

void	lex(char *line, t_main *main)
{
	main->lex = NULL;
	lexer(line, &(main->lex));
	for (t_pars *tmp = main->lex; tmp; tmp = tmp->next)
	{
		if (tmp->cmd)
			printf("%s\n", tmp->cmd);
	}
}