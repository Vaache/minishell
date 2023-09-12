/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 13:00:53 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/12 16:47:28 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid(t_main *main, t_env *env, int sb);
int	subshell_validation(t_tok *tmp, int *subshell);

int	check_valid(t_main *main, t_env *env, int sb)
{
	t_tok	*tmp;

	tmp = main->lex;
	while (tmp->next != NULL)
	{
		if (!subshell_validation(tmp, &sb))
			return (0);
		if (tmp->type == HEREDOC && !check_types(tmp->next->type))
			read_heredoc_input(main, tmp, NULL, env);
		if (check_types(tmp->type) && check_types(tmp->next->type) == 1)
			return (parse_error(2, type_is(tmp->next->type), 0));
		else if (check_types(tmp->type) == 2 && \
			!ft_strcmp(tmp->next->cmd, "(NULL)"))
		{
			if (tmp->next->next)
				return (parse_error(2, type_is(tmp->next->next->type), 0));
		}
		else if (check_types(tmp->type) && tmp->next->type == END)
			return (parse_error(2, "newline", 0));
		tmp = tmp->next;
	}
	if (sb > 0)
		return (parse_error(2, "newline", 0));
	return (1);
}

int	subshell_validation(t_tok *tmp, int *subshell)
{
	if (tmp->type == SUBSH_OPEN)
		(*subshell)++;
	else if (tmp->type == SUBSH_CLOSE)
		(*subshell)--;
	if (tmp->type == SUBSH_CLOSE && (!tmp->prev || \
		tmp->prev->type == SUBSH_OPEN || (*subshell) < 0))
		return (parse_error(2, ")", 0));
	if (tmp->type == SUBSH_OPEN && tmp->prev && !check_types(tmp->prev->type))
	{
		if (tmp->next->type != END && tmp->prev->type != SUBSH_OPEN)
			return (parse_error(2, tmp->next->cmd, 0));
		else if (tmp->prev->type != SUBSH_OPEN)
			return (parse_error(2, "newline", 0));
	}
	return (1);
}
