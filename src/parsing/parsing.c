/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 20:07:05 by rmkrtchy         #+#    #+#             */
/*   Updated: 2023/08/10 20:29:41 by rmkrtchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_main *main);
void	delete_node(t_pars **opstack);
void	push(t_pars **a, t_pars **b);
void	shunting_yard(t_pars **tmp, t_pars **postfix, t_pars **opstack);

void	delete_node(t_pars **opstack)
{
	t_pars	*tmp;

	if (!opstack || !(*opstack))
		return ;
	tmp = lstlast(*opstack);
	if (!tmp)
		*opstack = NULL;
	if (tmp->prev)
	{
		tmp->prev->next = NULL;
		tmp->prev = NULL;
		free(tmp->cmd);
		free(tmp);
	}
	else
	{
		free(tmp->cmd);
		free(tmp);
		*opstack = NULL;
	}
}

void	push(t_pars **a, t_pars **b)
{
	t_pars	*t1;
	t_pars	*t2;

	t1 = lstlast(*a);
	t2 = lstlast(*b);
	if (!t1)
		return ;
	else
	{
		if (t2)
			t2->next = t1;
		else
			*b = t1;
		if (t1->prev)
			t1->prev->next = NULL;
		else
			*a = NULL;
		t1->prev = t2;
	}
}

void	shunting_yard(t_pars **tmp, t_pars **postfix, t_pars **opstack)
{
	if ((*tmp)->prc == 0)
		lstback(postfix, lstadd((*tmp)->cmd, (*tmp)->type, \
			(*tmp)->prc, (*tmp)->flag));
	else if ((*tmp)->prc > 0)
	{
		if ((*tmp)->type == SUBSH_CLOSE)
		{
			while (*opstack && lstlast(*opstack)->type != SUBSH_OPEN)
				push(opstack, postfix);
			delete_node(&(*opstack));
			lstlast(*postfix)->subshell_code = 1;
		}
		else if ((*tmp)->type != SUBSH_OPEN)
		{
			while (*opstack && lstlast(*opstack)->prc >= (*tmp)->prc && \
					(*opstack)->type != SUBSH_OPEN)
				push(opstack, postfix);
			lstback(opstack, lstadd((*tmp)->cmd, (*tmp)->type, \
				(*tmp)->prc, (*tmp)->flag));
		}
		else
			lstback(opstack, lstadd((*tmp)->cmd, (*tmp)->type, \
				(*tmp)->prc, (*tmp)->flag));
	}
}

void	parsing(t_main *main)
{
	t_pars	*tmp;
	t_pars	*postfix;
	t_pars	*opstack;
	t_pars	*new;

	tmp = main->lex;
	postfix = NULL;
	opstack = NULL;
	new = NULL;
	while (tmp)
	{
		shunting_yard(&tmp, &postfix, &opstack);
		tmp = tmp->next;
	}
	while (opstack)
		push(&opstack, &postfix);
	main->pars = abstract_syntax_tree(main, &postfix, new);
	print_ast(main->pars, 0, 0);
}
