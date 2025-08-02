#include "cub3d.h"

int	validate_player_position(t_game *game)
{
	int	count;

	count = scan_for_player(game);
	if (count == 0)
	{
		printf("Error\nNo player found in map\n");
		return (0);
	}
	if (count > 1)
	{
		printf("Error\nMultiple players found in map\n");
		return (0);
	}
	game->player.pos_x = game->map.player_x + 0.5;
	game->player.pos_y = game->map.player_y + 0.5;
	return (1);
}

int	validate_map(t_game *game)
{
	if (!validate_player_position(game))
		return (0);
	if (!check_map_borders(game))
		return (0);
	return (1);
}
