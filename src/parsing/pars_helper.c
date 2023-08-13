/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 21:25:49 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/13 12:12:50 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pars	*pars_help(t_main **main, t_pars **tmp, t_pars **stack, t_pars *new);
t_pars	*pars_help2(t_main **main, t_pars **tmp, t_pars **stack, t_pars *new);

t_pars	*pars_help(t_main **main, t_pars **tmp, t_pars **stack, t_pars *new)
{
	t_pars	*ptr;

	ptr = (*tmp);
	while (ptr && ptr->cmd && (ptr->flag & 1) == 0)
	{
		push(stack, &(*main)->temp);
		ptr = lstlast(*stack);
	}
	if (ptr && ptr->cmd && (ptr->flag & 1) == 1)
	{
		new = lstadd(ptr->cmd, ptr->type, ptr->prc, ptr->flag);
		if (ptr->subshell_code)
			new->subshell_code = 1;
		delete_node(stack);
		while (main && (*main)->temp)
			push(&(*main)->temp, &new);
		return (new);
	}
	return (NULL);
}

t_pars	*pars_help2(t_main **main, t_pars **tmp, t_pars **stack, t_pars *new)
{
	t_pars	*ptr;

	ptr = (*tmp);
	new = lstadd(ptr->cmd, ptr->type, ptr->prc, ptr->flag);
	if (ptr->subshell_code)
		new->subshell_code = 1;
	delete_node(stack);
	new->right = most_prev(abstract_syntax_tree(*main, stack, new));
	new->left = most_prev(abstract_syntax_tree(*main, stack, new));
	if (check_types(new->type) == 2)
	{
		if (new->left)
			new->left->flag += 1 << 3;
		if (new->right)
			new->right->flag += 1 << 3;
		if (new && new->right && new->right->cmd)
			new->rpath = new->right->cmd;
		if (new && new->left && new->left->cmd)
			new->lpath = new->left->cmd;
	}
	return (new);
}
