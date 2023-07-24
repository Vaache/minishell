/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 20:03:51 by vhovhann          #+#    #+#             */
/*   Updated: 2023/07/24 19:12:30 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_intlen(int nb)
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

int	ft_print_int(int n, int fd)
{
	int	len;

	len = 0;
	if (n == -2147483648)
	{
		len += write(fd, "-2147483648", 11);
		return (len);
	}
	else if (n < 0)
	{
		len += write (fd, "-", 1);
		n = -n;
		ft_print_int(n, fd);
	}
	else if (n > 9)
	{
		ft_print_int(n / 10, fd);
		ft_print_int(n % 10, fd);
	}
	else
		ft_print_char(n + '0', fd);
	len += ft_intlen(n);
	return (len);
}
