/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_of_n.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:03:32 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/01 15:35:40 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_of_n(char *str, char **arr1, char **arr2, int i);

int	free_of_n(char *str, char **arr1, char **arr2, int i)
{
	if (i == 2)
	{
		free_2d(arr1);
		free_2d(arr2);
	}
	else if (i == 3)
	{
		free(str);
		free_2d(arr1);
		free_2d(arr2);
	}
	else
		free(str);
	return (0);
}

