#include "cub3d.h"

static int	get_map_color(t_game *game, int real_x, int real_y)
{
	if (game->map.grid[real_y][real_x] == '1')
		return (COLOR_WALL);
	else if (game->map.grid[real_y][real_x] == '0')
		return (COLOR_FLOOR);
	else
		return (COLOR_FLOOR);
}

static void	draw_map_cell(t_game *game, t_minimap_coords *coords)
{
	t_rect_data	rect;
	int			real_x;
	int			real_y;

	real_x = coords->start_x + coords->map_x;
	real_y = coords->start_y + coords->map_y;
	if (real_x >= 0 && real_x < game->map.width && \
		real_y >= 0 && real_y < game->map.height)
	{
		rect.color = get_map_color(game, real_x, real_y);
		rect.x = MINIMAP_OFFSET + coords->map_x * MINIMAP_SCALE;
		rect.y = MINIMAP_OFFSET + coords->map_y * MINIMAP_SCALE;
		rect.size = MINIMAP_SCALE - 1;
		draw_minimap_rect(game, &rect);
	}
}

static void	draw_minimap_grid(t_game *game, t_minimap_coords *coords)
{
	coords->map_y = 0;
	while (coords->map_y < MINIMAP_SIZE / MINIMAP_SCALE)
	{
		coords->map_x = 0;
		while (coords->map_x < MINIMAP_SIZE / MINIMAP_SCALE)
		{
			draw_map_cell(game, coords);
			coords->map_x++;
		}
		coords->map_y++;
	}
}

void	draw_minimap(t_game *game)
{
	t_minimap_coords	coords;
	t_rect_data			rect;

	rect.x = MINIMAP_OFFSET;
	rect.y = MINIMAP_OFFSET;
	rect.size = MINIMAP_SIZE;
	rect.color = COLOR_FLOOR;
	draw_minimap_rect(game, &rect);
	coords.start_x = (int)game->player.pos_x - \
		(MINIMAP_SIZE / MINIMAP_SCALE / 2);
	coords.start_y = (int)game->player.pos_y - \
		(MINIMAP_SIZE / MINIMAP_SCALE / 2);
	draw_minimap_grid(game, &coords);
	draw_minimap_player(game,
		MINIMAP_OFFSET + MINIMAP_SIZE / 2,
		MINIMAP_OFFSET + MINIMAP_SIZE / 2);
	draw_minimap_border(game);
}
