/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 13:00:53 by vhovhann          #+#    #+#             */
/*   Updated: 2023/11/30 15:55:17 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid(t_main *main, t_env *env, int *sb, int fl);
int	subshell_validation(t_tok *tmp, int *subshell);

int	check_valid(t_main *main, t_env *env, int *sb, int fl)
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
		if (tmp->type == HEREDOC && ft_strcmp(tmp->next->cmd, "(NULL)") && !fl)
			read_heredoc_input(main, tmp, NULL, env);
		if ((check_types(tmp->type) == 2 && tmp->type != HEREDOC) && !fl)
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
	if (tmp->type == SUBSH_CLOSE && (tmp->next->type == WORD \
	|| tmp->next->type == SQUOTE || tmp->next->type == DQUOTE))
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

void	valid_redir(t_tok **tok)
{
	t_tok	*tmp;

	tmp = (*tok);
	while (tmp && tmp->next)
	{
		if (!ft_strcmp(tmp->cmd, "(NULL)") && check_types(tmp->next->type) != 2)
		{
			tmp->next->prc = 0;
			tmp->next->flag = 1;
			tmp->next->prev = tmp->prev;
			tmp->prev->next = tmp->next;
			tmp->next = NULL;
			tmp->prev = NULL;
			free(tmp->cmd);
			free(tmp);
			tmp = (*tok);
			continue ;
		}
		else if ((tmp->type == WORD || tmp->type == DQUOTE || \
											tmp->type == SQUOTE) && \
			(tmp->prev == NULL || check_types(tmp->prev->type) == 1 || \
				tmp->prev->type == SUBSH_OPEN))
		{
			tmp->flag = 3;
			while (tmp && (tmp->type == WORD || tmp->type == DQUOTE || \
													tmp->type == SQUOTE))
				tmp = tmp->next;
		}
		if (!tmp)
			return ;
		tmp = tmp->next;
	}
}
