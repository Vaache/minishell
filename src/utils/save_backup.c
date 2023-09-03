/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_backup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 20:32:30 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/01 17:57:16 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_backup(t_main **main)
{
	(*main)->stdin_backup = dup(STDIN_FILENO);
	if ((*main)->stdin_backup == -1)
		perror("Minishell");
	(*main)->stdout_backup = dup(STDOUT_FILENO);
	if ((*main)->stdout_backup == -1)
		perror("Minishell");
}