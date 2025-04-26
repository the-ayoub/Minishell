

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}
/*#include <stdio.h>
int main (void)
{
	printf("%s"ft_lstlast(ft_lstnew_bonus("12234")));
}*/
