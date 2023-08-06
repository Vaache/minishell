/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:19:16 by vhovhann          #+#    #+#             */
/*   Updated: 2023/07/26 10:09:09 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr( void *str, int c, size_t n)
{
	size_t	i;

	i = 0;
	c %= 256;
	if (!str)
		return ((void *)0);
	while (i < n)
	{
		if (((char *)str)[i] == c)
			return ((unsigned char *)str + i);
		i++;
	}
	return ((void *)0);
}
