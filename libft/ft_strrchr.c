#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	ch;
	char	*lst;

	ch = (char) c;
	lst = NULL;
	while (*str)
	{
		if (*str == ch)
		{
			lst = (char *) str;
		}
		str++;
	}
	if (ch == '\0')
		return ((char *) str);
	return (lst);
}
