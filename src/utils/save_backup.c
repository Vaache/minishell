/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_backup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 20:32:30 by vhovhann          #+#    #+#             */
/*   Updated: 2023/12/04 18:26:44 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_backup(t_shell **main)
{
	(*main)->stdin_backup = dup(STDIN_FILENO);
	if ((*main)->stdin_backup == -1)
		perror("Minishell");
	(*main)->stdout_backup = dup(STDOUT_FILENO);
	if ((*main)->stdout_backup == -1)
		perror("Minishell");
	(*main)->hd->i = -1;
}
