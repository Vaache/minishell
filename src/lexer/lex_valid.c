/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 13:00:53 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/28 15:21:29 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid(t_main *main, t_env *env, int *sb, int flag);
int	subshell_validation(t_tok *tmp, int *subshell);

int	check_valid(t_main *main, t_env *env, int *sb, int flag)
{
	t_tok	*tmp;

	tmp = main->lex;
	while (tmp->next != NULL)
	{
		if (!subshell_validation(tmp, sb))
			return (0);
		if (check_types(tmp->type) == 2 && !ft_strcmp(tmp->next->cmd, "*"))
			return (ft_printf(2, "Minishell: *: ambiguous redirect\n"), 0);
		if (check_types(tmp->type) && check_types(tmp->next->type) == 1)
			return (parse_error(2, type_is(tmp->next->type), 0));
		if (check_types(tmp->type) == 1 && tmp->prev == NULL)
			return (parse_error(2, type_is(tmp->type), 0));
		if (check_types(tmp->type) == 2 && !ft_strcmp(tmp->next->cmd, "(NULL)"))
			if (tmp->next->next)
				return (parse_error(2, type_is(tmp->next->next->type), 0));
		if (check_types(tmp->type) && tmp->next->type == END)
			return (parse_error(2, "newline", 0));
		if (tmp->type == HEREDOC && ft_strcmp(tmp->next->cmd, "(NULL)") && flag == 0)
			read_heredoc_input(main, tmp, NULL, env);
		if ((check_types(tmp->type) == 2 && tmp->type != HEREDOC) && flag == 0)
			find_limiter(main, tmp->next);
		tmp = tmp->next;
	}
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
		return (parse_error(2, ")", 0 + (*subshell = 0)));
	if (tmp->type == SUBSH_CLOSE && (tmp->next->type == WORD || \
			tmp->next->type == SQUOTE || tmp->next->type == DQUOTE))
		return (parse_error(2, tmp->next->cmd, 0 + (*subshell = 0)));
	if (tmp->type == SUBSH_OPEN && tmp->prev && !check_types(tmp->prev->type))
	{
		if (tmp->next->type != END && tmp->prev->type != SUBSH_OPEN)
			return (parse_error(2, tmp->next->cmd, 0) + (*subshell = 0));
		else if (tmp->prev->type != SUBSH_OPEN)
			return (parse_error(2, "newline", 0) + (*subshell = 0));
	}
	return (1);
}
