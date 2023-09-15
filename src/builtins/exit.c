/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:24:35 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/14 19:59:37 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		minishell_exit(t_tok *stack, char **arr, t_env **env, char *s);
int		check_exit_status(char **arr, char *s, long long status, t_tok *stack);
int		exit_error_code(t_env *env, t_tok *stack);
char	*join_plus_minus(char *s, char c);
char	*check_zeroes(char *str);

int	minishell_exit(t_tok *stack, char **arr, t_env **env, char *s)
{
	long long	status;
	char		*str;

	str = NULL;
	if (strlen_2d(arr) == 1 && arr[1] == NULL)
		return (exit_error_code(*env, stack));
	if (arr[1] != NULL && ((arr[1][0] == '0' && arr[1][1] == '0') || \
			((arr[1][0] == '+' || arr[1][0] == '-') && arr[1][1] == '0')))
		stack->exit_tmp = check_zeroes(arr[1]);
	else
		stack->exit_tmp = arr[1];
	status = ft_atll(arr[1]);
	s = ft_itul(status);
	if (arr[1] && arr[1][0] == '+')
		str = join_plus_minus(s, arr[1][0]);
	else
		str = ft_strdup(s);
	free(s);
	status = check_exit_status(arr, str, status, stack);
	free(str);
	if (status == 1000)
		return (1);
	if (check_subsh(stack) || (stack->flag & _PIPE_))
		return (status);
	exit(status);
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

int	check_exit_status(char **arr, char *s, long long status, t_tok *stack)
{
	if (!check_subsh(stack) && !(stack->flag & _PIPE_))
		ft_printf(2, "exit\n");
	if (strlen_2d(arr) == 2 && ft_strcmp(s, stack->exit_tmp) == 0 && \
											check_digit(arr[1]) != 1)
		return ((unsigned char)status);
	else if (ft_strlen(s) > 19 || check_digit(arr[1]) == 1 || \
		ft_strcmp(s, stack->exit_tmp) != 0)
	{
		ft_printf(2, "Minishell: exit: %s: numeric argument required\n", \
			arr[1]);
		return (255);
	}
	else if (strlen_2d(arr) > 2 && check_digit(arr[1]) == 0)
	{
		ft_printf(2, "Minishell: exit: too many arguments\n");
		return (1000);
	}
	return (-1);
}

char	*join_plus_minus(char *s, char c)
{
	char	*str;

	str = NULL;
	if (c == '+')
		str = ft_strjoin("+", s, -1);
	else if (c == '-')
		str = ft_strjoin("-", s, -1);
	return (str);
}

char	*check_zeroes(char *str)
{
	char	*tmp;

	tmp = trim_zeroes(str);
	if (str[0] == '+' || str[0] == '-')
		tmp = join_plus_minus(str, tmp[0]);
	return (ft_strdup(tmp));
}
