/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 20:03:56 by vhovhann          #+#    #+#             */
/*   Updated: 2023/07/24 19:13:17 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_intlen(long int nb)
{
	int	len;

	len = 0;
	if (nb == 0)
	{
		len++;
		return (len);
	}
	while (nb != 0)
	{
		len++;
		nb = nb / 10;
	}
	return (len);
}

int	ft_print_uint(unsigned int n, int fd)
{
	if (n > 9)
	{
		ft_print_uint(n / 10, fd);
		ft_print_uint((n % 10), fd);
	}
	else
		ft_print_char((n + 48), fd);
	return (ft_intlen(n));
}
