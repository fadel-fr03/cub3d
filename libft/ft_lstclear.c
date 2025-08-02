#include "libft.h"

void	ft_lstclear(t_list **head, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	if (!head || !del)
		return ;
	current = *head;
	while (current)
	{
		next = current -> next;
		ft_lstdelone(current, del);
		current = next;
	}
	*head = NULL;
}
