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
void	check_last_red(t_tok **tmp);
void	push(t_tok **a, t_tok **b);
void	delete_node(t_tok **opstack);
void	shunting_yard(t_tok **tmp, t_tok **postfix, t_tok **opstack);

void	delete_node(t_tok **opstack)
{
	t_tok	*tmp;

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
		if (tmp->hdoc_fname)
			free(tmp->hdoc_fname);
		free(tmp);
	}
	else
	{
		free(tmp->cmd);
		if (tmp->hdoc_fname)
			free(tmp->hdoc_fname);
		free(tmp);
		*opstack = NULL;
	}
}

void	push(t_tok **a, t_tok **b)
{
	t_tok	*t1;
	t_tok	*t2;

	t1 = lstlast(*a);
	t2 = lstlast(*b);
	if (t1 == NULL)
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

void	shunting_yard(t_tok **tmp, t_tok **postfix, t_tok **opstack)
{
	if ((*tmp)->prc == 0)
		lstback(postfix, ast_branch(*tmp));
	else if ((*tmp)->prc > 0)
	{
		if ((*tmp)->type == SUBSH_CLOSE)
		{
			while (*opstack && lstlast(*opstack)->type != SUBSH_OPEN)
				push(opstack, postfix);
			delete_node(opstack);
			lstlast(*postfix)->subshell_code = 1;
		}
		else if ((*tmp)->type != SUBSH_OPEN)
		{
			while (*opstack && lstlast(*opstack)->prc >= (*tmp)->prc && \
					(*opstack)->type != SUBSH_OPEN)
				push(opstack, postfix);
			lstback(opstack, ast_branch(*tmp));
		}
		else
			lstback(opstack, ast_branch(*tmp));
	}
}

void	parsing(t_main *main)
{
	t_tok	*tmp;
	t_tok	*postfix;
	t_tok	*opstack;

	tmp = main->lex;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
			handle_heredoc_input(main, tmp, NULL);
		tmp = tmp->next;
	}
	tmp = main->lex;
	postfix = NULL;
	opstack = NULL;
	while (tmp)
	{
		shunting_yard(&tmp, &postfix, &opstack);
		tmp = tmp->next;
	}
	while (opstack)
		push(&opstack, &postfix);
	main->pars = abstract_syntax_tree(main, &postfix);
	print_ast(main->pars, 0, 0);
}
// void	check_last_red(t_tok **tmp)
// {
// 	if (((*tmp)->type == WRITE_TRUNC || (*tmp)->type == WRITE_APPEND) && (check_types((*tmp)->next->next->type) == 1 || (*tmp)->next->next->cmd == NULL))
// 		(*tmp)->last_red = 1;	
// 	else if ((*tmp)->type == HEREDOC && (check_types((*tmp)->next->next->type) == 1 || (*tmp)->next->next->cmd == NULL))
// 		(*tmp)->last_hdoc = 1;
// 	else if ((*tmp)->type == INPUT && (check_types((*tmp)->next->next->type) == 1 || (*tmp)->next->next->cmd == NULL))
// 		(*tmp)->last_input = 1;
// }

