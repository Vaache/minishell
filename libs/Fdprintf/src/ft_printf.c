/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 20:03:58 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/08 13:06:57 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static int	ft_chek_print(char c, va_list args, int fd)
{
	int	i;

	i = 0;
	if (c == 'c')
		i += ft_print_char(va_arg(args, int), fd);
	if (c == 'd' || c == 'i')
		i += ft_print_int(va_arg(args, int), fd);
	if (c == 's')
		i += ft_print_str(va_arg(args, char *), fd);
	if (c == 'u')
		i += ft_print_uint(va_arg(args, unsigned int), fd);
	if (c == 'x' || c == 'X')
		i += ft_print_hex(va_arg(args, unsigned int), c, fd);
	if (c == 'p')
		i += ft_print_ptr(va_arg(args, uintptr_t), fd);
	if (c == '%')
		i += write(fd, "%", 1);
	return (i);
}

int	ft_printf(int fd, char *s, ...)
{
	int		i;
	int		len;
	va_list	args;

	len = 0;
	i = 0;
	va_start(args, s);
	while (s[i] != '\0' && s[i])
	{
		if (s[i] == '%')
		{
			i++;
			len += ft_chek_print(s[i], args, fd);
		}
		else
			len += ft_print_char(s[i], fd);
		if (s[i] == '\0')
			return (len);
		i++;
	}
	va_end(args);
	return (len);
}
