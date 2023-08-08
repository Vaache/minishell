/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:01:17 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/08 13:04:53 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	j;
	size_t	k;
	size_t	i;
	char	*str;

	j = 0;
	i = 0;
	if (!s)
		return (0);
	k = ft_strlen(s);
	if (len > k)
		len = k;
	str = (char *)malloc(len + 1);
	if (!str)
		return (0);
	i = start;
	while (s[i] != '\0' && i < k && j < len)
		str[j++] = s[i++];
	str[j] = '\0';
	return (str);
}
