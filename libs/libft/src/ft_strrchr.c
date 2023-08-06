/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:54:48 by vhovhann          #+#    #+#             */
/*   Updated: 2023/07/26 10:09:09 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr( char *str, int c)
{
	int		i;
	char	*s;

	if (!str)
		return (NULL);
	s = (char *)str;
	i = ft_strlen(str);
	while (*s)
		s++;
	while (i >= 0)
	{
		if (*s == c % 256)
			return (s);
		s--;
		i--;
	}
	return (NULL);
}
