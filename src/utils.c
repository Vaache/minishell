/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:57:12 by vhovhann          #+#    #+#             */
/*   Updated: 2023/07/24 18:51:25 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2d(char **s, int i)
{
	while (i >= 0)
		free (s[i--]);
	free(s);
}

void	free_list(t_list **stack, char ***str)
{
	int		i;
	t_list	*temp;

	i = 0;
	temp = *stack;
	if (stack && (*stack))
	{
		while (temp)
		{
			temp = temp->next;
			free(*stack);
			*stack = temp;
		}
		free((*stack));
	}
	while ((*str)[i])
	{
		free((*str)[i]);
		i++;
	}
	free(*str);
}

int	strlen_2d(char **str)
{
	int	i;

	i = 0;
	while (str && str[i] != NULL)
		i++;
	return (i);
}

unsigned long long int	ft_atll(char *str)
{
	long long	num;
	int			sing;

	sing = -1;
	num = 0;
	if (!str)
		return (0);
	while (*str && ((*str == ' ') || *str == '\t' || *str == '\r'
			|| *str == '\f' || *str == '\v' || *str == '\n'))
		++str;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sing *= -1;
		++str;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		++str;
	}
	return (num * sing);
}
