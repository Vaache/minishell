/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:57:12 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/12 15:32:35 by vhovhann         ###   ########.fr       */
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
	int			i;

	sing = 1;
	num = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i] && ((str[i] == ' ') || str[i] == '\t' || str[i] == '\r'
			|| str[i] == '\f' || str[i] == '\v' || str[i] == '\n'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sing *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num * sing);
}

int	check_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str && str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (1);
	}
	return (0);
}
