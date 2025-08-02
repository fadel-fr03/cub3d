#include "cub3d.h"

// Close window and exit
int	close_window(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}
