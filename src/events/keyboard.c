#include "cub3d.h"

// Handle key press
int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys[K_W] = 1;
	else if (keycode == KEY_A)
		game->keys[K_A] = 1;
	else if (keycode == KEY_S)
		game->keys[K_S] = 1;
	else if (keycode == KEY_D)
		game->keys[K_D] = 1;
	else if (keycode == KEY_LEFT)
		game->keys[K_LEFT] = 1;
	else if (keycode == KEY_RIGHT)
		game->keys[K_RIGHT] = 1;
	else if (keycode == KEY_ESC)
		close_window(game);
	return (0);
}

// Handle key release
int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys[K_W] = 0;
	else if (keycode == KEY_A)
		game->keys[K_A] = 0;
	else if (keycode == KEY_S)
		game->keys[K_S] = 0;
	else if (keycode == KEY_D)
		game->keys[K_D] = 0;
	else if (keycode == KEY_LEFT)
		game->keys[K_LEFT] = 0;
	else if (keycode == KEY_RIGHT)
		game->keys[K_RIGHT] = 0;
	return (0);
}

// Move forward
void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.dir_x * MOVE_SPEED;
	new_y = game->player.pos_y + game->player.dir_y * MOVE_SPEED;
	if (game->map.grid[(int)game->player.pos_y][(int)new_x] != '1')
		game->player.pos_x = new_x;
	if (game->map.grid[(int)new_y][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
}

// Move backward
void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - game->player.dir_x * MOVE_SPEED;
	new_y = game->player.pos_y - game->player.dir_y * MOVE_SPEED;
	if (game->map.grid[(int)game->player.pos_y][(int)new_x] != '1')
		game->player.pos_x = new_x;
	if (game->map.grid[(int)new_y][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
}
