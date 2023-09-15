/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:52:49 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/15 21:53:04 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push_redir(t_tok *to, t_tok *from);
void	pop_redir(t_tok *tok);

void	push_redir(t_tok *to, t_tok *from)
{
	from->prev->next = from->next;
	from->next->prev = from->prev;
	from->next = to->next;
	to->next = from;
	from->prev = to;
	if (from->flag & (1 << 2))
		from->flag -= (1 << 2);
}

void	pop_redir(t_tok *tok)
{
	tok->prev->next = tok->next;
	tok->next->prev = tok->prev;
	tok->prev = NULL;
	tok->next = NULL;
	free(tok->cmd);
	free(tok);
}
