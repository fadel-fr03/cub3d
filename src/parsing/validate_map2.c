#include "cub3d.h"

static int	check_reach(char **tmp, t_game *g)
{
	int	x;
	int	y;

	y = -1;
	while (++y < g->map.height)
	{
		x = -1;
		while (++x < g->map.width)
		{
			if (g->map.grid[y][x] == '0' && tmp[y][x] != 'F')
			{
				printf("Error\nMap can't reach (%d,%d)\n", x, y);
				return (0);
			}
		}
	}
	return (1);
}

int	check_map_borders(t_game *g)
{
	char	**tmp;

	tmp = create_map_copy(g);
	if (!tmp)
		return (mem_error());
	flood_fill(g, tmp, g->map.player_x, g->map.player_y);
	if (!check_closed(tmp, g))
	{
		free_map(tmp);
		return (0);
	}
	if (!check_reach(tmp, g))
	{
		free_map(tmp);
		return (0);
	}
	free_map(tmp);
	return (1);
}

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	set_player(t_game *game, int x, int y)
{
	game->map.player_x = x;
	game->map.player_y = y;
	game->map.player_dir = game->map.grid[y][x];
	game->map.grid[y][x] = '0';
}

int	scan_for_player(t_game *game)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = -1;
	while (++y < game->map.height)
	{
		x = -1;
		while (++x < game->map.width)
		{
			if (is_player_char(game->map.grid[y][x]))
			{
				set_player(game, x, y);
				count++;
			}
		}
	}
	return (count);
}
