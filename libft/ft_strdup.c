#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*copy;

	len = ft_strlen((char *)s) + 1;
	copy = malloc(len);
	if (!copy)
		return (NULL);
	if (copy != NULL)
		ft_strlcpy(copy, (char *)s, len);
	return (copy);
}
