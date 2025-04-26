

#include "libft.h"

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
/*#include <stdio.h>
int main (void)
{
	int c;
	c = '8';
	printf("%i",ft_isalnum(c));
	return(0);
}*/
