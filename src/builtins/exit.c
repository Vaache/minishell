/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:24:35 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/19 22:14:32 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_exit(char **arr, t_env *env);

void	minishell_exit(char **arr, t_env *env)
{
	char		*s;
	t_env		*tmp;
	long long	exit_num;

	s = NULL;
	tmp = env;
	if (arr[1] != NULL && (arr[1][0] == '0' || \
			arr[1][0] == '+' || arr[1][1] == '0'))
		arr[1] = trim_zeroes(arr[1]);
	exit_num = ft_atll(arr[1]);
	s = ft_itul(exit_num);
	if (arr[1] && arr[1][0] == '+')
		s = ft_strjoin("+", s, -1);
	if (strlen_2d(arr) == 1 && arr[1] == NULL)
	{
		while (tmp)
		{
			if (!ft_strcmp(tmp->key, "$?"))
				break;
			tmp = tmp->next;
		}
		ft_printf(1, "exit\n");
		free_2d(arr);
		exit(ft_atoi(tmp->data));
	}
	else if (strlen_2d(arr) == 2 && ft_strcmp(s, arr[1]) == 0)
	{
		ft_printf(2, "exit\n");
		free_2d(arr);
		if (exit_num == 0)
			exit (EXIT_SUCCESS);
		exit (exit_num % 256);
	}
	else if (ft_strlen(s) > 19 || check_digit(arr[1]) == 1 || \
		ft_strcmp(s, arr[1]) != 0)
	{
		ft_printf(2, "exit\n");
		ft_printf(2, "Minishell: exit: %s: numeric argument required\n", \
			arr[1]);
		free_2d(arr);
		free(s);
		exit(255);
	}
	else if (strlen_2d(arr) > 2 && check_digit(arr[1]) == 0)
	{
		ft_printf(1, "exit\n");
		ft_printf(1, "Minishell: exit: too many arguments\n");
		free_2d(arr);
	}
	if (s)
	{
		free(s);
		s = NULL;
	}
}