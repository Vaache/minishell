/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:22:08 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/24 21:06:41 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_wcard(char	*string);

void	get_file(char *file)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (!dir)
	{
		perror("opendir");
		return ;
	}
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if ()
	}
}

void	open_wcard(char	*string)
{
}
