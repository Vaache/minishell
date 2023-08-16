/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:19:34 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/16 11:42:33 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*restore_cmds_line(t_pars *stack);

char	*restore_cmds_line(t_pars *stack)
{
	char	*cmd;
	int		mode;
	t_pars	*tmp;

	cmd = NULL;
	tmp = stack;
	while (tmp && tmp->cmd)
	{
		mode = (tmp->flag & (1 << 1)) && 1;
		if (!cmd || (mode == 0 && \
			(tmp->type == DQUOTE || tmp->type == SQUOTE ||\
			tmp->prev->type == DQUOTE || tmp->prev->type == SQUOTE)))
				cmd = ft_strjoin(cmd, tmp->cmd, 1);
		else
			cmd = strjoin_mode(cmd, tmp->cmd, 0);
		tmp = tmp->next;
	}
	cmd[ft_strlen(cmd)] = '\0';
	return (cmd);
}