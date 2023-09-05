/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes_fds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:27:04 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/05 20:51:54 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_pipes(int fd[2]);
int	_close3_(int fd1, int fd2, int fd3);
int	_close2_(int fd1, int fd2);
int	_close_(int fd);

int	_close_(int fd)
{
	if (close(fd) < 0)
	{
		perror("minishell");
		return (-10);
	}
	return (0);
}

int	_close2_(int fd1, int fd2)
{
	if (fd1 >= 0 && close(fd1) < 0)
	{
		perror("minishell");
		return (-10);
	}
	if (fd2 >= 0 && close(fd2) < 0)
	{
		perror("minishell");
		return (-10);
	}
	return (0);
}

int	_close3_(int fd1, int fd2, int fd3)
{
	if (close(fd1) < 0 || close(fd2) < 0 || close(fd3) < 0)
	{
		perror("minishell");
		return (-10);
	}
	return (0);
}

int	close_pipes(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
	return (1);
}
