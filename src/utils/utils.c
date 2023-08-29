/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:57:12 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/29 16:12:12 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_n2d(char **s, int i)
{
	while (i >= 0)
		free (s[i--]);
	free(s);
}

int	free_2d(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s && s[i])
		free (s[i++]);
	free(s);
	return (0);
}

int	strlen_2d(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str && str[i] != NULL)
		i++;
	return (i);
}

unsigned long long int	ft_atll(char *str)
{
	long long	num;
	int			sing;

	sing = 1;
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

int	check_digit(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0')
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || \
			(str[i] >= 'a' && str[i] <= 'Z'))
			return (1);
		i++;
	}
	return (0);
}
