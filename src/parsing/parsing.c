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
			lstlast(*postfix)->sub = 1;
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

void	print_ast(t_tok *ast, int indent, int lrc)
{
	int	i;

	i = 0;
	if (!ast)
		return ;
	else if (ast->type == END)
		return (print_ast(ast->right, indent, 0));
	print_ast(ast->right, indent + 1, 1);
	while (i++ < indent)
		printf("\t");
	if (lrc == 0)
		printf("\033[38;5;46m╠══════\033[0m[%s][%d][%d]\n", ast->cmd, \
		(ast->flag & _PIPE_) && 1, ast->sub);
	else if (lrc == 1)
		printf("\033[38;5;46m╔══════\033[0m[%s][%d][%d]\n", ast->cmd, \
		(ast->flag & _PIPE_) && 1, ast->sub);
	else if (lrc == 2)
		printf("\033[38;5;46m╚══════\033[0m[%s][%d][%d]\n", ast->cmd, \
		(ast->flag & _PIPE_) && 1, ast->sub);
	if (ast->next)
		print_ast(ast->next, indent + 1, 2);
	print_ast(ast->left, indent + 1, 2);
}

void	parsing(t_main *main)
{
	t_tok	*tmp;
	t_tok	*postfix;
	t_tok	*opstack;

	postfix = NULL;
	opstack = NULL;
	tmp = main->lex;
	while (tmp)
	{
		shunting_yard(&tmp, &postfix, &opstack);
		tmp = tmp->next;
	}
	while (opstack)
		push(&opstack, &postfix);
	main->pars = abstract_syntax_tree(main, &postfix);
	// print_ast(main->pars, 0, 0);
}
