/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 10:53:35 by vhovhann          #+#    #+#             */
/*   Updated: 2023/07/23 21:55:15 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_unset(char *arr, t_env_list *my_env)
{
	t_env_list	*tmp;

	tmp = my_env;
	if (tmp != NULL && arr && (arr[0] == '_' || ((arr[0] >= 'a' && arr[0] <= 'z') || \
	(arr[0] >= 'A' && arr[0] <= 'Z'))))
	{
		while (tmp != NULL)
		{
			if (ft_strcmp(arr, tmp->key) == 0)
			{
				tmp->flag = 1;
				break ;
			}
			tmp = tmp->next;
		}
	}
	else
		printf("Minishell: unset: %s: not a valid identifier\n", arr);
	if (ft_strchr(arr, ' '))
		printf("Minishell: unset: %s: not a valid identifier\n", arr);
}