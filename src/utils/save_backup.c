/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_backup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 20:32:30 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/31 20:38:29 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_backup(t_main **main)
{
	t_main	*tmp;

	tmp = (*main);
	tmp->stdin_backup = dup(STDIN_FILENO);
	if (tmp->stdin_backup == -1)
		perror("Minishell");
	tmp->stdout_backup = dup(STDOUT_FILENO);
	if (tmp->stdout_backup == -1)
		perror("Minishell");
}