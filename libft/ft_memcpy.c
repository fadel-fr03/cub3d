#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t num_bytes)
{
	unsigned char			*dest;
	const unsigned char		*src;

	dest = destination;
	src = source;
	while (num_bytes > 0)
	{
		*dest = *src;
		dest++;
		src++;
		num_bytes--;
	}
	return (destination);
}
