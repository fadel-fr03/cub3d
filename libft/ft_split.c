#include "libft.h"

int	word_count(const char *s, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	if (!s || !*s)
		return (counter);
	while (s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		counter++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (counter);
}

char	*helper(const char *s, int start, char c)
{
	int		len_word;
	int		j;
	char	*word;

	len_word = 0;
	while (s[len_word + start] && s[len_word + start] != c)
		len_word++;
	word = (char *)malloc(sizeof(char) * (len_word + 1));
	if (!word)
		return (NULL);
	j = 0;
	while (j < len_word)
	{
		word[j] = s[start + j];
		j++;
	}
	word[j] = '\0';
	return (word);
}

char	**ft_free(char **result)
{
	size_t	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (NULL);
}

char	**ft_malloc(const char *s, char c)
{
	char	**result;

	result = (char **)malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	return (result);
}

char	**ft_split(const char *s, char c)
{
	int		i;
	int		j;
	char	**result;

	if (!s)
		return (NULL);
	result = ft_malloc(s, c);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		result[j] = helper(s, i, c);
		if (!result[j])
			return (ft_free(result));
		j++;
		while (s[i] && s[i] != c)
			i++;
	}
	result[j] = NULL;
	return (result);
}
