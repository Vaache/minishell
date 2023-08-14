/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:53:27 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/14 11:57:43 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strjoin_mode(char *s1, char *s2, int mode);
char	*trim_zeroes(char *s);

char	*trim_zeroes(char *s)
{
	long	i;
	int		j;
	char	*str;

	j = 0;
	str = NULL;
	if (s[0] == '0' || (s[0] == '0' && s[1] == '0'))
	{
		while (s && s[j] != '\0')
		{
			if (s[j] == '-' || s[j] == '+')
				j++;
			while (s[j] != '\0' && s[j] == '0')
				j++;
			if (s[j] != '0')
				break ;
		}
		if (s[j] != '\0' && s[j] != '0')
			str = (char *)malloc(sizeof(char) * (j + 1));
		if (!str)
			return (NULL);
		i = 0;
		while (s[j] != '\0')
			str[i++] = s[j++];
		str[i] = '\0';
		if (s[0] != '\0' && s[0] == '-')
			str = ft_strjoin("-", str, 1);
		return (str);
	}
	return (s);
}

char	*strjoin_mode(char *s1, char *s2, int mode)
{
	if (mode == 1)
		s1 = ft_strjoin(s1, "\n", 1);
	else
		s1 = ft_strjoin(s1, " ", 1);
	s1 = ft_strjoin(s1, s2, 1);
	return (s1);
}