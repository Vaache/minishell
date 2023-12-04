/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:29:21 by vhovhann          #+#    #+#             */
/*   Updated: 2023/12/04 18:26:44 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok	*abstract_syntax_tree(t_shell *main, t_tok **stack);
t_tok	*ast_end(t_shell *main, t_tok *new, t_tok *tmp, t_tok **stack);
t_tok	*ast_left_right(t_shell *main, t_tok *new, t_tok *tmp, t_tok **stack);
t_tok	*ast_create_cmd(t_shell *main, t_tok *new, t_tok *tmp, t_tok **stack);
t_tok	*most_prev(t_tok *stack);

t_tok	*most_prev(t_tok *stack)
{
	t_tok	*tmp;

	tmp = stack;
	if (!tmp)
		return (NULL);
	while (tmp && tmp->prev != NULL)
		tmp = tmp->prev;
	return (tmp);
}

t_tok	*abstract_syntax_tree(t_shell *main, t_tok **stack)
{
	t_tok	*tmp;
	t_tok	*new;

	tmp = lstlast(*stack);
	new = NULL;
	if (!tmp)
		return (NULL);
	else if (tmp->type == END)
		new = ast_end(main, new, tmp, stack);
	else if (check_types(tmp->type))
		new = ast_left_right(main, new, tmp, stack);
	else if (tmp && tmp->type != END)
		new = ast_create_cmd(main, new, tmp, stack);
	return (new);
}

t_tok	*ast_left_right(t_shell *main, t_tok *new, t_tok *tmp, t_tok **stack)
{
	new = ast_branch(tmp);
	if (tmp->sub)
		new->sub = 1;
	delete_node(stack);
	new->right = most_prev(abstract_syntax_tree(main, stack));
	new->left = most_prev(abstract_syntax_tree(main, stack));
	if (new && check_types(new->type) == 2)
	{
		if (new->left)
			new->left->flag += _REDIR_;
		if (new->right)
			new->right->flag += _REDIR_;
	}
	return (new);
}

t_tok	*ast_create_cmd(t_shell *main, t_tok *new, t_tok *tmp, t_tok **stack)
{
	while (tmp && tmp->cmd && (tmp->flag & 1) == 0)
	{
		push(stack, &main->temp);
		tmp = lstlast(*stack);
	}
	if (tmp && tmp->cmd && (tmp->flag & 1) == 1)
	{
		new = ast_branch(tmp);
		if (tmp->sub)
			new->sub = 1;
		delete_node(stack);
		while (main && main->temp)
			push(&main->temp, &new);
		return (new);
	}
	return (NULL);
}

t_tok	*ast_end(t_shell *main, t_tok *new, t_tok *tmp, t_tok **stack)
{
	new = ast_branch(tmp);
	delete_node(stack);
	new->right = most_prev(abstract_syntax_tree(main, stack));
	if (!new)
		return (NULL);
	return (new);
}
