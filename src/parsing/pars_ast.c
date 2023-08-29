/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:29:21 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/29 14:02:12 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pars	*abstract_syntax_tree(t_main *main, t_pars **stack);
void	print_ast(t_pars *ast, int indent, int lrc);
t_pars	*most_prev(t_pars *stack);

void	print_types(t_pars *ptr)
{
	if (!ptr)
		printf("%p", NULL);
	while (ptr)
	{
		if (ptr->next != NULL)
			printf("%s [%d] ", ptr->cmd, ptr->type & (1 << 6));
		else
			printf("%s [%d]", ptr->cmd, ptr->type & (1 << 6));
		ptr = ptr->next;
	}
	printf("\n");
}

void	print_ast(t_pars *ast, int indent, int lrc)
{
	int	i;

	i = 0;
	if (!ast)
		return ;
	else if (ast->type == END)
	{
		print_ast(ast->right, indent, 0);
		return ;
	}
	print_ast(ast->right, indent + 1, 1);
	while (i++ < indent)
	{
		printf("\t");
	}
	if (lrc == 0)
		printf("\033[38;5;46m╠══════\033[0m[%s][%d][%d]\n", ast->cmd, (ast->flag & _PIPE_) && 1, ast->subshell_code);
	else if (lrc == 1)
		printf("\033[38;5;46m╔══════\033[0m[%s][%d][%d]\n", ast->cmd, (ast->flag & _PIPE_) && 1, ast->subshell_code);
	else if (lrc == 2)
		printf("\033[38;5;46m╚══════\033[0m[%s][%d][%d]\n", ast->cmd, (ast->flag & _PIPE_) && 1, ast->subshell_code);
	if (ast->next)
		print_ast(ast->next, indent + 1, 2);
	print_ast(ast->left, indent + 1, 2);
}

t_pars	*most_prev(t_pars *stack)
{
	t_pars	*tmp;

	tmp = stack;
	if (!tmp)
		return (NULL);
	while (tmp && tmp->prev != NULL)
		tmp = tmp->prev;
	if (!tmp)
		return (NULL);
	return (tmp);
}

t_pars	*abstract_syntax_tree(t_main *main, t_pars **stack)
{
	t_pars	*tmp;
	t_pars	*new;

	tmp = lstlast(*stack);
	new = NULL;
	if (!tmp)
		return (NULL);
	else if (tmp->type == END)
	{
		new = lstadd(tmp->cmd, tmp->type, tmp->prc, tmp->flag);
		delete_node(stack);
		new->right = most_prev(abstract_syntax_tree(main, stack));
		if (!new)
			return (NULL);
		return (new);
	}
	else if (check_types(tmp->type))
	{
		new = lstadd(tmp->cmd, tmp->type, tmp->prc, tmp->flag);
		if (tmp->subshell_code)
			new->subshell_code = 1;
		delete_node(stack);
		new->right = most_prev(abstract_syntax_tree(main, stack));
		new->left = most_prev(abstract_syntax_tree(main, stack));
		if (new && check_types(new->type) == 2)
		{
			if (new->left)
			{
				new->left->flag += _REDIR_;
				if (new->left->cmd)
					new->lpath = new->left->cmd;
			}
			if (new->right)
			{
				new->right->flag += _REDIR_;
				if (new->right->cmd)
					new->rpath = new->right->cmd;
			}
		}
		return (new);
	}
	else if (tmp && tmp->type != END)
	{
		while (tmp && tmp->cmd && (tmp->flag & 1) == 0)
		{
			push(stack, &main->temp);
			tmp = lstlast(*stack);
		}
		if (tmp && tmp->cmd && (tmp->flag & 1) == 1)
		{
			new = lstadd(tmp->cmd, tmp->type, tmp->prc, tmp->flag);
			if (tmp->subshell_code)
				new->subshell_code = 1;
			delete_node(stack);
			while (main && main->temp)
				push(&main->temp, &new);
			return (new);
		}
	}
	return (new);
}
