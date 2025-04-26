
#include "libft.h"

long	ft_atoi(const char *str)
{
	int		sign;
	long	i;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
/*
#include <stdlib.h>
#include <stdio.h>
int main(void)
{
	printf("%i\n", ft_atoi("  +-3"));
	printf("org: %i", atoi("  +-3"));
}*/
