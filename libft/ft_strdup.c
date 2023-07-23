/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 20:13:36 by vhovhann          #+#    #+#             */
/*   Updated: 2023/07/23 20:43:34 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		len;
	char	*s;

	// if (!str)
	// 	return (0);
	len = 0;
	while (str && str[len])
		len++;
	s = (char *)malloc(len + 1);
	if (s == NULL)
		return (NULL);
	while (len >= 0)
	{
		s[len] = str[len];
		len--;
	}
	return (s);
}
