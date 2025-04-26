

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(int))
{
	t_list	*temp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		del ((*lst)->content);
		free (*lst);
		*lst = temp;
	}
}
