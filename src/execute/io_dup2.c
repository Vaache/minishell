/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_dup2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 21:40:30 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/12 16:45:18 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	io_dup2(int _stdin_, int _stdout_)
{
	if (_stdin_ > 0)
	{
		if (dup2(_stdin_, STDIN_FILENO) < 0)
		{
			perror("minishell");
			return (EXIT_FAILURE);
		}
		close(_stdin_);
	}
	if (_stdout_ > 0)
	{
		if (dup2(_stdout_, STDOUT_FILENO) < 0)
		{
			perror("minishell");
			return (EXIT_FAILURE);
		}
		close(_stdout_);
	}
	return (0);
}

int	io_backup_dup2(int _stdin_backup_, int _stdout_backup_)
{
	if (_stdin_backup_ > 0)
	{
		if (dup2(_stdin_backup_, STDIN_FILENO) < 0)
		{
			perror("minishell");
			return (EXIT_FAILURE);
		}
		close(_stdin_backup_);
	}
	if (_stdout_backup_ > 0)
	{
		if (dup2(_stdout_backup_, STDOUT_FILENO) == -1)
		{
			perror("Minishell");
			return (1);
		}
		close(_stdout_backup_);
	}
	return (0);
}
