#include "cub3d.h"

// Check if position is valid and within bounds
static int	is_valid_pos(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map.width || y < 0 || y >= game->map.height)
		return (0);
	return (1);
}

// Flood fill to check if map is closed
void	flood_fill(t_game *game, char **temp_map, int x, int y)
{
	if (!is_valid_pos(game, x, y))
		return ;
	if (temp_map[y][x] == '1' || temp_map[y][x] == 'F' || temp_map[y][x] == ' ')
		return ;
	temp_map[y][x] = 'F';
	flood_fill(game, temp_map, x + 1, y);
	flood_fill(game, temp_map, x - 1, y);
	flood_fill(game, temp_map, x, y + 1);
	flood_fill(game, temp_map, x, y - 1);
}

// Create a copy of the map for flood fill
char	**create_map_copy(t_game *game)
{
	char	**copy;
	int		y;

	copy = malloc(sizeof(char *) * (game->map.height + 1));
	if (!copy)
		return (NULL);
	y = 0;
	while (y < game->map.height)
	{
		copy[y] = ft_strdup(game->map.grid[y]);
		if (!copy[y])
		{
			while (--y >= 0)
				free(copy[y]);
			free(copy);
			return (NULL);
		}
		y++;
	}
	copy[game->map.height] = NULL;
	return (copy);
}

int	mem_error(void)
{
	printf("Error\nMemory allocation failed\n");
	return (0);
}

int	check_closed(char **tmp, t_game *g)
{
	int	x;
	int	y;

	y = -1;
	while (++y < g->map.height)
	{
		x = -1;
		while (++x < g->map.width)
		{
			if ((x == 0 || x == g->map.width - 1
					|| y == 0 || y == g->map.height - 1)
				&& tmp[y][x] == 'F')
			{
				printf("Error\nMap is not closed at (%d,%d)\n", x, y);
				printf("Character at position: '%c'\n", g->map.grid[y][x]);
				return (0);
			}
		}
	}
	return (1);
}
