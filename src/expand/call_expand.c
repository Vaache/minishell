/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:40:30 by vhovhann          #+#    #+#             */
/*   Updated: 2023/11/01 22:48:50 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		call_expand(t_tok *stack, t_env *env);
void	destroy_exp(t_exp *exp);

int	call_expand(t_tok *stack, t_env *env)
{
	t_tok	*tmp;
	char	*str;
	t_exp	exp;

	tmp = stack;
	exp.i = -1;
	exp.l = 0;
	exp.str = NULL;
	exp.s = NULL;
	str = NULL;
	if (stack->cmd[0] == '\0')
		return (0);
	while (tmp)
	{
		if (ft_strchr(tmp->cmd, '$') && tmp->type != SQUOTE)
		{
			str = ft_strdup(expand(tmp->cmd, &env, &exp));
			free(tmp->cmd);
			tmp->cmd = ft_strdup(str);
			free(str);
			destroy_exp(&exp);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	destroy_exp(t_exp *exp)
{
	if (exp->i)
		exp->i = -1;
	if (exp->l)
		exp->l = 0;
	if (exp->str)
	{
		free(exp->str);
		exp->str = NULL;
	}
	if (exp->s)
	{
		free(exp->s);
		exp->s = NULL;
	}
}
