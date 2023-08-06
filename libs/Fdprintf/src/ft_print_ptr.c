/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 20:22:47 by vhovhann          #+#    #+#             */
/*   Updated: 2023/07/24 19:13:03 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_ptr_len(uintptr_t num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num /= 16;
	}
	return (len);
}

static void	ft_put_ptr(uintptr_t ptr, int fd)
{
	if (ptr >= 16)
	{
		ft_put_ptr(ptr / 16, fd);
		ft_put_ptr(ptr % 16, fd);
	}
	else
	{
		if (ptr <= 9)
			ft_print_char(ptr + '0', fd);
		else
			ft_print_char(ptr - 10 + 'a', fd);
	}
}

int	ft_print_ptr(uintptr_t ptr, int fd)
{
	int	len;

	len = 0;
	len += write(fd, "0x", 2);
	if (ptr == 0)
		len += write(fd, "0", 1);
	else
	{
		ft_put_ptr(ptr, fd);
		len += ft_ptr_len(ptr);
	}
	return (len);
}
