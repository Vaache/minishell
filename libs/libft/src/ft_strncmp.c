/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 17:14:28 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/14 18:57:36 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] || s2[i]) && (i < n))
	{
		if (s1[i] != s2[i])
			return (1);
		if (s1[i] != s2[i])
			return (-1);
		i++;
	}
	return (0);
}

/*int main()
{
	char p[] = "abcdaaa";
	char c[] = "abcd";

	printf("%d", ft_strncmp(p,c,10));
}*/