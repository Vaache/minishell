/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 10:53:35 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/07 16:20:19 by vhovhann         ###   ########.fr       */
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

	i = -1;
	l = -1;
	while (line && line[++i])
	{
		start = i;
		while (line[i])
		{
			if (line[i] == '"')
				l = handel_dquotes(pars, line, i, start) + 1;	
			else if (line[i] == '\'')
				l = handel_squotes(pars, line, i, start) + 1;
			else if (line[i] == '|' && line[i + 1] == '|')
				l = handel_xor(pars, line, i, start);
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
}