
#include "libft.h"

int	ft_pointer(size_t dir)
{
	int	count;

	if (!dir || dir == 0)
	{
		if (write(1, "(nil)", 5) == -1)
			return (-1);
		return (5);
	}
	count = 2;
	if (write(1, "0x", 2) == -1)
		return (-1);
	count += ft_hexadecimal_a(dir, "0123456789abcdef");
	return (count);
}

int	ft_hexadecimal_a(size_t nb, char *base)
{
	int	count;

	count = 0;
	if (nb < 16)
		count += ft_putchar1(base[nb]);
	if (nb >= 16)
	{
		count += ft_hexadecimal_a(nb / 16, base);
		count += ft_hexadecimal_a(nb % 16, base);
	}
	return (count);
}

void	ft_unsigned(unsigned int n, int *count)
{
	char	c;

	if (n >= 10)
		ft_unsigned(n / 10, count);
	c = (n % 10) + '0';
	if (write(1, &c, 1) == -1)
		return ((*count) = -1, (void)0);
	(*count)++;
}

void	ft_putnbr1(int n, int *count)
{
	char	c;

	if (n == -2147483648)
	{
		if (write(1, "-2147483648", 11) == -1)
			return ((*count) = -1, (void)0);
		*count = 11;
		return ;
	}
	if (n < 0)
	{
		if (write(1, "-", 1) == -1)
			return ((*count) = -1, (void)0);
		(*count)++;
		n = -n;
	}
	if (n >= 10)
		ft_putnbr1(n / 10, count);
	c = (n % 10) + '0';
	if (write(1, &c, 1) == -1)
		return ((*count) = -1, (void)0);
	(*count)++;
}

int	ft_putstr1(char *str)
{
	int	i;
	int	count;

	if (str == NULL)
	{
		if (write(1, "(null)", 6) == 1)
			return (-1);
		count = 6;
		return (count);
	}
	i = 0;
	count = 0;
	while (str[i])
	{
		ft_putchar1((int)(str[i]));
		i++;
		count++;
	}
	return (count);
}
