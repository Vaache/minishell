/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:56:28 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/16 12:02:35 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_unset(char *str, t_env *my_env);
void	minishell_unset(char **arr, t_env *my_env);

void	minishell_unset(char **arr, t_env *my_env)
{
	int		i;

	i = 0;
	while (arr && arr[++i])
		check_unset(arr[i], my_env);
}

void	check_unset(char *str, t_env *my_env)
{
	t_env	*tmp;

	tmp = my_env;
	if (tmp != NULL && str && (str[0] == '_' || \
		((str[0] >= 'a' && str[0] <= 'z') || \
	(str[0] >= 'A' && str[0] <= 'Z'))))
	{
		while (tmp != NULL)
		{
			if (ft_strcmp(str, tmp->key) == 0)
			{
				tmp->flag = 1;
				break ;
			}
			tmp = tmp->next;
		}
	}
	else
		ft_printf(2, "Minishell: unset: %s: not a valid identifier\n", str);
	if (ft_strchr(str, ' '))
		ft_printf(2, "Minishell: unset: %s: not a valid identifier\n", str);
}
