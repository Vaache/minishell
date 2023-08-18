/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 20:11:09 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/18 16:20:58 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_isspace(char *str, int start, int i);
int		is_delim(t_pars	*pars);
int		check_types(t_type type);
char	*type_is(t_type type);
int		check_valid(t_main *main);

int	ft_isspace(char *str, int start, int i)
{
	while (start < i && str[start])
	{
		if (str[start] != ' ' && str[start] != '\t')
			return (0);
		start++;
	}
	return (1);
}

char	*type_is(t_type type)
{
	if (type == XAND)
		return ("&&");
	else if (type == XOR)
		return ("||");
	else if (type == PIPE)
		return ("|");
	else if (type == HEREDOC)
		return ("<<");
	else if (type == INPUT)
		return ("<");
	else if (type == WRITE_APPEND)
		return (">>");
	else if (type == WRITE_TRUNC)
		return (">");
	else if (type == END)
		return ("END");
	return ("");
}

int	check_types(t_type type)
{
	if (!type)
		return (0);
	if (type == XOR || type == XAND || type == PIPE)
		return (1);
	if (type == HEREDOC || type == WRITE_APPEND)
		return (2);
	if (type == INPUT || type == WRITE_TRUNC)
		return (2);
	return (0);
}

int	is_delim(t_pars	*pars)
{
	t_pars	*tmp;

	tmp = pars;
	if (!tmp)
		return (2);
	tmp = lstlast(tmp);
	if (tmp->type == PIPE || tmp->type == HEREDOC)
		return (1);
	else if (tmp->type == SUBSH_CLOSE || tmp->type == SUBSH_OPEN)
		return (1);
	else if (tmp->type == WRITE_APPEND || tmp->type == WRITE_TRUNC || \
		tmp->type == INPUT)
		return (1);
	else if (tmp->type == XOR || tmp->type == XAND)
		return (1);
	else
		return (0);
}

int	check_valid(t_main *main)
{
	t_pars	*tmp;

	tmp = main->lex;
	if (!tmp)
		return (0);
	while (tmp->next != NULL)
	{
		if (check_types(tmp->type) && check_types(tmp->next->type) == 1)
			return (parse_error(2, type_is(tmp->next->type), 1));
		else if (check_types(tmp->type) && tmp->next->type == END)
			return (parse_error(2, "newline", -1));
		tmp = tmp->next;
	}
	return (1);
}


