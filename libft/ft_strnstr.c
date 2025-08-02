#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t len)
{
	size_t	i;
	size_t	j;

	if (!str1 && len == 0)
		return (NULL);
	if (*str2 == '\0')
		return ((char *)str1);
	i = 0;
	while (i < len && str1[i])
	{
		if (str1[i] == str2[0])
		{
			j = 0;
			while (str2[j] && (i + j) < len)
			{
				if (str1[i + j] != str2[j])
					break ;
				j++;
			}
			if (str2[j] == '\0')
				return ((char *)str1 + i);
		}
		i++;
	}
	return (NULL);
}
