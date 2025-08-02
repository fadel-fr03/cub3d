#include "libft.h"

int	check_is_in_set(char c, const char *set)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(set);
	i = 0;
	while (i < len)
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	len;
	char	*empty;

	if (!s1)
		return (NULL);
	start = 0;
	len = ft_strlen(s1);
	while (check_is_in_set(s1[start], set))
		start++;
	if (start == len)
	{
		empty = (char *)malloc(1);
		if (!empty)
			return (NULL);
		empty[0] = '\0';
		return (empty);
	}
	while (check_is_in_set(s1[len - 1], set))
		len--;
	return (ft_substr(s1, start, len - start));
}
