#include "libft.h"

void	ft_lstiter(t_list *head, void (*f)(void *))
{
	if (f)
	{
		while (head != NULL)
		{
			f(head -> content);
			head = head -> next;
		}
	}
}
