

#include "libft.h"

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
/*#include <stdio.h>
int main(void)
{
	int	c;
	c = 'a';
	printf("%i",ft_isalpha(c));
	return(0);
}*/
