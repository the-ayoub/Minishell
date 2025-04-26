

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(int))
{
	t_list	*tmp;

	if (!lst || !f)
		return ;
	while (lst != NULL)
	{
		tmp = lst->next;
		f(lst->content);
		lst = tmp;
	}
}
