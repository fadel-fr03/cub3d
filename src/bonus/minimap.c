#include "cub3d.h"

void	draw_minimap_rect(t_game *game, t_rect_data *rect)
{
	int	i;
	int	j;
	int	screen_x;
	int	screen_y;

	i = 0;
	while (i < rect->size)
	{
		j = 0;
		while (j < rect->size)
		{
			screen_x = rect->x + i;
			screen_y = rect->y + j;
			if (screen_x >= MINIMAP_OFFSET && \
				screen_x < MINIMAP_OFFSET + MINIMAP_SIZE && \
				screen_y >= MINIMAP_OFFSET && \
				screen_y < MINIMAP_OFFSET + MINIMAP_SIZE)
			{
				my_mlx_pixel_put(&game->mlx, screen_x, screen_y, rect->color);
			}
			j++;
		}
		i++;
	}
}

void	draw_minimap_player(t_game *game, int center_x, int center_y)
{
	t_rect_data	rect;
	int			i;
	int			line_x;
	int			line_y;

	rect.x = center_x - 1;
	rect.y = center_y - 1;
	rect.size = 3;
	rect.color = COLOR_PLAYER;
	draw_minimap_rect(game, &rect);
	i = 0;
	while (i < 15)
	{
		line_x = center_x + (int)(game->player.dir_x * i);
		line_y = center_y + (int)(game->player.dir_y * i);
		if (line_x >= MINIMAP_OFFSET && \
			line_x < MINIMAP_OFFSET + MINIMAP_SIZE && \
			line_y >= MINIMAP_OFFSET && \
			line_y < MINIMAP_OFFSET + MINIMAP_SIZE)
		{
			my_mlx_pixel_put(&game->mlx, line_x, line_y, COLOR_VIEW_CONE);
		}
		i++;
	}
}

static void	draw_horizontal_border(t_game *game, t_border_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < MINIMAP_BORDER)
	{
		x = 0;
		while (x < data->border_width)
		{
			my_mlx_pixel_put(&game->mlx,
				data->border_start_x + x,
				data->border_start_y + y,
				COLOR_BORDER);
			my_mlx_pixel_put(&game->mlx,
				data->border_start_x + x,
				MINIMAP_OFFSET + MINIMAP_SIZE + y,
				COLOR_BORDER);
			x++;
		}
		y++;
	}
}

static void	draw_vertical_border(t_game *game, t_border_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < MINIMAP_BORDER)
	{
		y = 0;
		while (y < data->border_height)
		{
			my_mlx_pixel_put(&game->mlx,
				data->border_start_x + x,
				data->border_start_y + y,
				COLOR_BORDER);
			my_mlx_pixel_put(&game->mlx,
				MINIMAP_OFFSET + MINIMAP_SIZE + x,
				data->border_start_y + y,
				COLOR_BORDER);
			y++;
		}
		x++;
	}
}

void	draw_minimap_border(t_game *game)
{
	t_border_data	data;

	data.border_start_x = MINIMAP_OFFSET - MINIMAP_BORDER;
	data.border_start_y = MINIMAP_OFFSET - MINIMAP_BORDER;
	data.border_width = MINIMAP_SIZE + 2 * MINIMAP_BORDER;
	data.border_height = MINIMAP_SIZE + 2 * MINIMAP_BORDER;
	draw_horizontal_border(game, &data);
	draw_vertical_border(game, &data);
}
