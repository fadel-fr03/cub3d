#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	index;
	size_t	str_1_len;
	size_t	total_len;
	char	*new_str;

	if (!s1 || !s2)
		return (NULL);
	str_1_len = ft_strlen(s1);
	total_len = ft_strlen(s2) + str_1_len;
	new_str = (char *)malloc(sizeof(char) * total_len + 1);
	if (!new_str)
		return (NULL);
	index = 0;
	while (s1[index])
	{
		new_str[index] = s1[index];
		index++;
	}
	while (s2[index - str_1_len])
	{
		new_str[index] = s2[index - str_1_len];
		index++;
	}
	new_str[index] = '\0';
	return (new_str);
}
