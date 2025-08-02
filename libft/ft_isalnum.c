#include "libft.h"

int	ft_isalnum(int a)
{
	if (ft_isalpha(a) == 1 || ft_isdigit(a) == 1)
		return (1);
	else
		return (0);
}
