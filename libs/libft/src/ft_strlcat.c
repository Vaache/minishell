/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:07:33 by vhovhann          #+#    #+#             */
/*   Updated: 2023/07/26 10:08:03 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	k;
	size_t	len;

	if (!src)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	len = ft_strlen(dst);
	if (dstsize <= len)
		return (dstsize + ft_strlen(src));
	i = 0;
	k = ft_strlen(dst);
	while (src[i] != '\0' && k + 1 < dstsize)
	{
		dst[k] = src[i];
		i++;
		k++;
	}
	dst[k] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[i]));
}
