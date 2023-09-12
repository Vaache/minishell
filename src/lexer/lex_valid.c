/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 13:00:53 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/12 15:07:16 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid(t_main *main, t_env *env);
int	valid_subsh(t_tok *stack, int subshell);
int	subsh_checks(t_tok *tmp);

int	check_valid(t_main *main, t_env *env)
{
	t_tok	*ptr;
	int		sb;

	ptr = main->lex;
	sb = 0;
	if (!valid_subsh(ptr, 0))
		return (0);
	while (ptr->next != NULL)
	{
		if (ptr->type == HEREDOC && !check_types(ptr->next->type))
			read_heredoc_input(main, ptr, NULL, env);
		if (check_types(ptr->type) && check_types(ptr->next->type) == 1)
			return (parse_error(2, type_is(ptr->next->type), 0));
		else if (check_types(ptr->type) == 2 && \
			!ft_strcmp(ptr->next->cmd, "(NULL)"))
		{
			if (ptr->next->next)
				return (parse_error(2, type_is(ptr->next->next->type), 0));
		}
		else if (check_types(ptr->type) && ptr->next->type == END)
			return (parse_error(2, "newline", 0));
		ptr = ptr->next;
	}
	return (1);
}

int	valid_subsh(t_tok *stack, int subshell)
{
	t_tok	*tmp;

	tmp = stack;
	while (tmp)
	{
		if (tmp->type == SUBSH_OPEN)
			subshell++;
		else if (tmp->type == SUBSH_CLOSE)
			subshell--;
		if (!subsh_checks(tmp))
			return (0);
		tmp = tmp->next;
	}
	if (subshell != 0)
		return (parse_error(2, ")", 0));
	return (1);
}

int	subsh_checks(t_tok *tmp)
{
	if (tmp->type == SUBSH_OPEN && tmp->next && \
			tmp->next->type == SUBSH_CLOSE)
		return (parse_error(2, ")", 0));
	if (tmp->type == SUBSH_OPEN && tmp->prev && \
				tmp->next && !check_types(tmp->prev->type) && \
				tmp->next->type != END)
	{
		printf("%s\n", tmp->next->cmd);	
		return (parse_error(2, tmp->next->cmd, 0));
	}
	if (tmp->type == SUBSH_CLOSE && tmp->next && \
					!check_types(tmp->next->type) && \
			tmp->next->type != END && ft_strcmp(tmp->next->cmd, "(NULL)"))
		return (parse_error(2, tmp->next->cmd, 0));
	if (tmp->type == SUBSH_OPEN && check_types(tmp->next->type) && \
					tmp->next && tmp->next->next && \
					tmp->next->next->type == SUBSH_CLOSE)
		return (parse_error(2, tmp->next->cmd, 0));
	return (1);
}
