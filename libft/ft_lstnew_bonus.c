
#include "libft.h"

t_list	*ft_lstnew(int content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
/*
int main (void )
{
	t_list	*hola;

	hola = ft_lstnew("afhgjkk");
	printf("%s",(char*)hola->content);
}
*/
