/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_dup2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 21:40:30 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/13 20:38:25 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	io_dup2(int _stdin_, int _stdout_)
{
	if (_stdin_ != -42)
	{
		if (dup2(_stdin_, STDIN_FILENO) < 0)
		{
			perror("minishell");
			return (EXIT_FAILURE);
		}
	}
	if (_stdout_ != -42)
	{
		if (dup2(_stdout_, STDOUT_FILENO) < 0)
		{
			perror("minishell");
			return (EXIT_FAILURE);
		}
	}
	return (0);
}

int	io_backup_dup2(int _stdin_backup_, int _stdout_backup_)
{
	if (_stdin_backup_ != -42)
	{
		if (dup2(_stdin_backup_, STDIN_FILENO) < 0)
		{
			perror("minishell");
			return (EXIT_FAILURE);
		}
	}
	if (_stdout_backup_ != -42)
	{
		if (dup2(_stdout_backup_, STDOUT_FILENO) == -1)
		{
			perror("Minishell");
			return (1);
		}
	}
	return (0);
}
