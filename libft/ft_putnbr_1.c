#include <unistd.h>
#include <stdlib.h>

void ft_putchar(int c)
{
	write(1, &c, 1);
}

void ft_putnbr_1(int nb)
{
	long n = nb;
	if (nb < 0)
	{
		write(1, "-", 1);
		n *= -1;
	}
	while (1)
	{
		if(n > 9)
			n /= 10;
		else if (n == 0)
			exit (1);
		else
			ft_putchar(nb % 10 + 48);
	}
}
#include <stdio.h>
int main()
{
	ft_putnbr_1(1);
}