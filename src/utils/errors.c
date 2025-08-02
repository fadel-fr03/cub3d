#include "cub3d.h"

// Exit with error message
void	exit_error(char *message, t_game *game)
{
	printf("Error\n%s\n", message);
	cleanup_game(game);
	exit(1);
}

// Free 2D array
void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

// Skip whitespace characters
char	*skip_spaces(char *str)
{
	while (*str && (*str == ' ' || *str == '\t'
			|| *str == '\n' || *str == '\r' || *str == '\v' || *str == '\f'))
		str++;
	return (str);
}

// Count elements in a split array
int	count_split_elements(char **split)
{
	int	count;

	count = 0;
	while (split && split[count])
		count++;
	return (count);
}

// Free split array
void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
