/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:24:35 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/10 10:23:06 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		minishell_exit(t_tok *stack, char **arr, t_env **env, char *s);
int		check_exit_status(char **arr, char *s, int exit_num, t_tok *stack);
int		exit_error_code(t_env *env, t_tok *stack);
char	*join_plus_minus(char *s, char c);
char	*check_zeroes(char *str);

int	minishell_exit(t_tok *stack, char **arr, t_env **env, char *s)
{
	long long	exit_num;
	char		*str;

	if (arr[1] != NULL)
	{
		str = arr[1];
		arr[1] = check_zeroes(arr[1]);
		free(str);
	}
	exit_num = ft_atll(arr[1]);
	s = ft_itul(exit_num);
	if (arr[1] && (arr[1][0] == '+' || arr[1][0] == '-'))
	{
		str = s;
		s = join_plus_minus(s, arr[1][0]);
		free(str);
	}
	if (strlen_2d(arr) == 1 && arr[1] == NULL)
		return (exit_error_code(*env, stack));
	exit_num = check_exit_status(arr, s, exit_num, stack);
	if (exit_num == 1000)
		return (1);
	if (check_subsh(stack) || (stack->flag & _PIPE_))
		return (exit_num);
	exit(exit_num);
}

int	exit_error_code(t_env *env, t_tok *stack)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "$?"))
			break ;
		tmp = tmp->next;
	}
	if (check_subsh(stack) || (stack->flag & _PIPE_))
		return (ft_atoi(tmp->data));
	ft_printf(2, "exit\n");
	exit (ft_atoi(tmp->data));
}

int	check_exit_status(char **arr, char *s, int exit_num, t_tok *stack)
{
	if (!check_subsh(stack) && !(stack->flag & _PIPE_))
		ft_printf(2, "exit\n");
	if (strlen_2d(arr) == 2 && ft_strcmp(s, arr[1]) == 0)
	{
		if (exit_num == 0)
			return (0);
		return (exit_num % 256);
	}
	else if (ft_strlen(s) > 19 || check_digit(arr[1]) == 1 || \
		ft_strcmp(s, arr[1]) != 0)
	{
		ft_printf(2, "Minishell: exit: %s: numeric argument required\n", \
			arr[1]);
		return (255);
	}
	else if (strlen_2d(arr) > 2 && check_digit(arr[1]) == 0)
	{
		ft_printf(2, " Minishell: exit: too many arguments\n");
		free(s);
		return (1000);
	}
	return (-1);
}

char	*join_plus_minus(char *s, char c)
{
	char	*str;

	str = ft_strdup(s);
	if (c == '+')
		s = ft_strjoin("+", str, -1);
	else if (c == '-')
		s = ft_strjoin("-", str, -1);
	free(str);
	return (s);
}

char	*check_zeroes(char *str)
{
	char	*tmp;

	if (str != NULL && ((str[0] == '0' && str[1] == '0') || \
			((str[0] == '+' || str[0] == '-') && str[1] == '0')))
	{
		tmp = ft_strdup(str);
		str = trim_zeroes(tmp);
		free(tmp);
	}
	return (ft_strdup(str));
}
