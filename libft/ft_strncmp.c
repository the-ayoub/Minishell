

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2)
		return (0);
	if (n == 0)
		return (0);
	i = 0;
	while (i < (n - 1) && *s1 == *s2 && (*s1 || *s2))
	{
		s1++;
		s2++;
		i++;
	}
	return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
}
/*int main (void)
{
	char *s1 = "hola";
	char *s2 = "holai";


	printf ("ft:%i\n",ft_strncmp(s1, s2, 4));
	printf ("org:%i\n:",strncmp(s1, s2, 4));
}*/
