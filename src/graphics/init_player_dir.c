#include "cub3d.h"

static void	north_south_direction(t_game *game)
{
	if (game->map.player_dir == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else if (game->map.player_dir == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
}

static void	east_west_direction(t_game *game)
{
	if (game->map.player_dir == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
	else if (game->map.player_dir == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
}

// Initialize player direction based on spawn orientation
void	init_player_direction(t_game *game)
{
	if (game->map.player_dir == 'N' || game->map.player_dir == 'S')
		north_south_direction(game);
	else if (game->map.player_dir == 'E' || game->map.player_dir == 'W')
		east_west_direction(game);
}
