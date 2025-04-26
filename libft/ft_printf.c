
#include "libft.h"

int	ft_printf(const char *str, ...)
{
	int			i;
	va_list		args;
	int			count;

	i = 0;
	count = 0;
	va_start(args, str);
	while (str && str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			i++;
			count += conditionals(str[i], args);
		}
		else if (str[i])
		{
			if (str[i] == '%')
				return (-1);
			ft_putchar1(str[i]);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
}

int	conditionals(char c, va_list args)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_putchar1(va_arg(args, int));
	else if (c == 's')
		count += ft_putstr1(va_arg(args, char *));
	else if (c == 'p')
		count += ft_pointer(va_arg(args, size_t));
	else if (c == 'd')
		ft_putnbr1(va_arg(args, int), &count);
	else if (c == 'i')
		ft_putnbr1(va_arg(args, int), &count);
	else if (c == 'u')
		ft_unsigned(va_arg(args, unsigned int), &count);
	else if (c == 'x')
		count += ft_hexadecimal_a(va_arg(args, unsigned int),
				"0123456789abcdef");
	else if (c == 'X')
		count += ft_hexadecimal_a(va_arg(args, unsigned int),
				"0123456789ABCDEF");
	else if (c == '%')
		count += ft_putchar1((int)c);
	return (count);
}

int	ft_putchar1(int c)
{
	int	count;

	count = 0;
	if (write(1, &c, 1) == -1)
		return (-1);
	count++;
	return (count);
}

/*int	main(void)
{
	//int	a = -2147483648;
	//char	*h = "holaquetal" ;
	printf("%i\n", ft_printf("%u", -1));
	printf("%i", printf("%u", -2));
	return (0);
}*/
