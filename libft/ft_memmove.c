#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t num_bytes)
{
	unsigned char		*dest;
	const unsigned char	*src;

	dest = (unsigned char *) destination;
	src = (const unsigned char *) source;
	if (dest < src)
		ft_memcpy (dest, src, num_bytes);
	else
	{
		while (num_bytes > 0)
		{
			dest[num_bytes - 1] = src[num_bytes - 1];
			num_bytes--;
		}
	}
	return (destination);
}
