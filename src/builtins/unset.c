/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:56:28 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/24 20:08:44 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_unset(char *str);
int	minishell_unset(char **arr, t_env *my_env);

int	minishell_unset(char **arr, t_env *my_env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	while (arr && arr[++i])
	{
		if (check_unset(arr[i]))
			return (1);
		tmp = my_env;
		while (tmp != NULL)
		{
			if (ft_strcmp(arr[i], tmp->key) == 0)
			{
				tmp->flag = 1;
				break ;
			}
			tmp = tmp->next;
		}
	}
	return (0);
}

int	check_unset(char *str)
{
	int		i;

	i = -1;
	while (str && str[++i])
	{
		if (str[0] != '=' && str[i] == '=')
			break ;
		if (ft_isalpha(str[i]) == 0 && str[i] != '_')
		{
			ft_printf(2, "Minishell: unset: `%s': not a %s\n", \
					str, "valid identifier");
			return (1);
		}
	}
	return (0);
}
