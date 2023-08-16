/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:53:27 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/16 14:19:38 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strjoin_mode(char *s1, char *s2, int mode);
char	*trim_zeroes(char *s);
char	*search_redir(char *str);
int		error_code(int error_num);

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
			str = ft_strjoin("-", str, -1);
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

char	*search_redir(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str && str[i])
	{
		if (str[i + 1] && ((str[i] == '&' && str[i + 1] == '&') || 
			(str[i] == '|' && str[i + 1] == '|') || \
			(str[i] == '<' && str[i + 1] == '<') || \
			(str[i] == '>' && str[i + 1] == '>')))
			{
				tmp = ft_substr(str + i, 0, 2);
				return (tmp);
			}
		else if (str[i] && (str[i] == '&' || str[i] == '|' || \
			str[i] == '<' || str[i] == '>'))
			{
				tmp = ft_substr(str + i, 0, 1);
				return (tmp);
			}
		i++;
	}
	return (NULL);
}

int	error_code(int error_num)
{
	if (error_num == 256)
		return (1);
	return (error_num % 256);
}
