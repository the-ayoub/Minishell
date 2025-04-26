

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c = c + 32;
	return (c);
}

/*int	main (int argc, char **argv)
{
	if (argc == 2)
		printf("%c", ft_tolower((int)*argv[1]));
	return (0);
}*/
