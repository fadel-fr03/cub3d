#include "cub3d.h"

static void	draw_ceiling(t_game *game, int x, int draw_start)
{
	int	y;

	y = 0;
	while (y < draw_start)
	{
		my_mlx_pixel_put(&game->mlx, x, y, create_rgb(game->ceiling_color));
		y++;
	}
}

static void	draw_texture(t_game *game, int x, t_ray *ray, int tex_num)
{
	int		y;
	int		tex_y;
	int		color;
	double	step;
	double	tex_pos;

	step = 1.0 * game->textures[tex_num].height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= game->textures[tex_num].height)
			tex_y = game->textures[tex_num].height - 1;
		else if (tex_y < 0)
			tex_y = 0;
		color = get_texture_color(&game->textures[tex_num], ray->tex_x, tex_y);
		my_mlx_pixel_put(&game->mlx, x, y, color);
		tex_pos += step;
		y++;
	}
}

static void	draw_floor(t_game *game, int x, int draw_end)
{
	int	y;

	y = draw_end + 1;
	while (y < WIN_HEIGHT)
	{
		my_mlx_pixel_put(&game->mlx, x, y, create_rgb(game->floor_color));
		y++;
	}
}

void	draw_vertical_line(t_game *game, int x, t_ray *ray, int tex_num)
{
	draw_ceiling(game, x, ray->draw_start);
	draw_texture(game, x, ray, tex_num);
	draw_floor(game, x, ray->draw_end);
}
