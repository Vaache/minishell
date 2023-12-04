/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_second_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:28:10 by vhovhann          #+#    #+#             */
/*   Updated: 2023/12/04 18:26:44 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		execute_second_arg(t_shell *main, t_tok *stack, t_env *env);
t_tok	*find_second_arg(t_tok *stack);

int	execute_second_arg(t_shell *main, t_tok *stack, t_env *env)
{
	t_tok	*tmp;

	tmp = find_second_arg(stack);
	if (!tmp)
		return (0);
	stack->err_code = cmds_execute(main, tmp, &env, 0);
	return (stack->err_code);
}

t_tok	*find_second_arg(t_tok *stack)
{
	t_tok	*tmp;

	if (!stack->right->next && lstsize(stack->right) > 1)
		return (NULL);
	tmp = stack->right->next;
	while (tmp && !(tmp->flag & (1 << 1)))
		tmp = tmp->next;
	if (!tmp || tmp->type == END)
		return (NULL);
	return (tmp);
}
