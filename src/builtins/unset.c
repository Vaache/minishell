/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:56:28 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/14 12:45:53 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_unset(char *arr, t_env *my_env);
void	minishell_unset(char *str, t_env *my_env);

void	minishell_unset(char *str, t_env *my_env)
{
	char	**arr;
	int		i;

	arr = ft_split(str, ' ');
	i = 0;
	while (arr && arr[++i])
		check_unset(arr[i], my_env);
	free_2d(arr, strlen_2d(arr));
}

void	check_unset(char *arr, t_env *my_env)
{
	t_env	*tmp;

	tmp = my_env;
	if (tmp != NULL && arr && (arr[0] == '_' || \
		((arr[0] >= 'a' && arr[0] <= 'z') || \
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
		ft_printf(2, "Minishell: unset: %s: not a valid identifier\n", arr);
	if (ft_strchr(arr, ' '))
		ft_printf(2, "Minishell: unset: %s: not a valid identifier\n", arr);
}
