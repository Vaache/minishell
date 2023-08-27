/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:22:08 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/27 11:40:40 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wcard_logic(char *pattern, char *string);

void	get_file(char *path, t_wcard *wcard)
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
		if (!ft_strchr(path, '.') || entry->d_name[0] != '.')
			if (wcard_logic(path, entry->d_name))
				lstback_wcard(&wcard, lstadd_wcard(path));
				
	}
}

int	wcard_logic(char *pattern, char *string)
{
	char	*p;
	int		star;

	star = 0;
	p = NULL;
	if (pattern[0] != '.' && string[0] == '.')
		return (0);
	while (*string != '\0')
	{
		if (*pattern == *string)
		{
			pattern++;
			string++;
		} 
		else if (*pattern == '*')
		{
			star = 1;
			p = pattern++;
		} 
		else if (star)
		{
			pattern = p + 1;
			++string;
		}
		else
			return 0;
	}
	while (*pattern == '*')
		pattern++;
	return (*pattern == '\0');
}
