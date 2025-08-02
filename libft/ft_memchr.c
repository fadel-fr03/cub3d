#include "libft.h"

void	*ft_memchr(const void *ptr, int value, size_t num)
{
	const unsigned char	*p;
	unsigned char		val;
	size_t				i;

	i = 0;
	val = (unsigned char) value;
	p = (const unsigned char *) ptr;
	while (i < num)
	{
		if (p[i] == val)
			return ((void *) p + i);
		i++;
	}
	return (NULL);
}
