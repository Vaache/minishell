/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:50:39 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/04 20:22:21 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_echo(char **arr);

void	minishell_echo(char **arr)
{
	int	j;
	int	i;

	i = 1;
	if (arr[1] == NULL)
		ft_printf(1, "\n");
	if (arr[i] && ft_strncmp(arr[i], "-n", 2) == 0)
	{
		while (arr[i] != NULL && ft_strncmp(arr[i], "-n", 2) == 0)
		{
			j = 1;
			while (arr[i][j] && arr[i][j] == 'n')
				j++;
			if (arr[i][j] != '\0')
				break ;
			else if (arr[i + 1] && ft_strncmp(arr[i + 1], "-n", 2) != 0)
			{
				while (arr[i + 1])
				{
					ft_printf(1, "%s", arr[i + 1]);
					if (arr[i + 2])
						ft_printf(1, " ");
					i++;
					if (arr[i + 1] == NULL)
						return ;
				}
			}
			i++;
		}
		while (arr[i] && i != 1)
		{
			ft_printf(1, "%s", arr[i]);
			if (arr[i + 1])
				ft_printf(1, " ");
			i++;
			if (arr[i] == NULL)
				return ;
		}
	}
	if (arr[i] && (ft_strncmp(arr[i], "-n", 2) != 0 || i == 1))
	{
		while (arr[i])
		{
			ft_printf(1, "%s", arr[i]);
			if (arr[i + 1])
				ft_printf(1, " ");
			i++;
			if (arr[i] == NULL)
				ft_printf(1, "\n");
		}
	}	
}
