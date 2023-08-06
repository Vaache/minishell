#include <unistd.h>
#include <stdlib.h>

void ft_putchar(int c, int fd)
{
	write(fd, &c, 1);
}

void ft_putnbr_1(int nb, int fd)
{
	long n = nb;
	if (nb < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	while (1)
	{
		if(n > 9)
			n /= 10;
		else if (n == 0)
			exit (1);
		else
			ft_putchar(nb % 10 + 48, fd);
	}
}
