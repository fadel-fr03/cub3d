#include "libft.h"

void	ft_lstadd_back(t_list **head, t_list *new)
{
	t_list	*last;

	if (!new || !head)
		return ;
	if (*head)
	{
		last = ft_lstlast(*head);
		last -> next = new;
	}
	else
		*head = new;
}
