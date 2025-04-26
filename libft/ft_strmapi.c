
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char				*result;
	unsigned int		i;

	i = 0;
	result = ft_calloc((ft_strlen(s) + 1), sizeof(char));
	while (s[i])
	{
		result[i] = (*f)(i, s[i]);
		i++;
	}
	return (result);
}
