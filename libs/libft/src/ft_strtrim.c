/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:54:38 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/08 13:04:43 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_chek_str(char s, char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == s)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*str;

	i = 0;
	start = 0;
	if (!s1)
		return (0);
	while (s1[start] && ft_chek_str(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_chek_str(s1[end - 1], set))
		end--;
	str = (char *)malloc(sizeof(*s1) * (end - start + 1));
	if (!str)
		return (0);
	i = 0;
	while (end > start)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
