

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		len_s;	
	int		i;

	len_s = ft_strlen(s);
	dest = malloc((len_s + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
