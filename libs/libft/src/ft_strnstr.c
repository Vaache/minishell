/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:27:11 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/08 13:04:28 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *s1, char *s2, size_t n)
{
	size_t	i;
	size_t	k;
	size_t	len;

	if (!s1 && !s2)
		return (0);
	i = 0;
	len = ft_strlen(s2);
	k = 0;
	if (s2[k] == '\0')
		return ((char *)s1 + i);
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && i < n)
	{
		while (s1[i + k] == s2[k] && i < n)
		{
			if (k == len - 1 && i + k < n)
				return ((char *)s1 + i);
			k++;
		}
		i++;
		k = 0;
	}
	return (0);
}
