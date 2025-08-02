#include "libft.h"

int	numlen(int num)
{
	size_t	len;

	len = 0;
	if (num <= 0)
		len++;
	while (num != 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}

int	ft_negative(char *char_num, int x, int num)
{
	char_num[0] = '-';
	return (x = num * (-1));
}

char	*ft_itoa(int num)
{
	char			*char_num;
	size_t			len;
	unsigned int	x;

	len = numlen(num);
	x = (unsigned int) num;
	char_num = (char *)malloc((len + 1) * sizeof(char));
	if (!char_num)
		return (NULL);
	char_num[len] = '\0';
	if (num < 0)
		x = ft_negative(char_num, x, num);
	if (num == 0)
		char_num[len - 1] = '0';
	else
	{
		while (x > 0)
		{
			char_num[--len] = (x % 10) + '0';
			x /= 10;
		}
	}
	return (char_num);
}
