#include "libft.h"

char	*ft_substr(char const *s, unsigned int start,
			size_t len)
{
	size_t	i;
	char	*memo;

	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
	{
		start = 0;
		len = 0;
	}
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	memo = (char *)malloc(sizeof(char) * (len + 1));
	if (!memo)
		return (NULL);
	i = 0;
	while (i < len)
	{
		memo[i] = s[start + i];
		i++;
	}
	memo[i] = '\0';
	return (memo);
}
