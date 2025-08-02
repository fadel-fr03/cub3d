#include "cub3d.h"

// Calculate which texture to use and X coordinate on texture
void	calculate_texture_coordinates(t_ray *ray, t_game *game, int *tex_num)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			*tex_num = TEX_EA;
		else
			*tex_num = TEX_WE;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			*tex_num = TEX_SO;
		else
			*tex_num = TEX_NO;
	}
	if (ray->side == 0)
		ray->wall_x = game->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = game->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)game->textures[*tex_num].width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = game->textures[*tex_num].width - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = game->textures[*tex_num].width - ray->tex_x - 1;
}

// Get color value from texture
int	get_texture_color(t_texture *texture, int x, int y)
{
	char	*dst;
	int		color;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	dst = texture->addr + (y * texture->line_length + x
			* (texture->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

// Create RGB color from color struct
int	create_rgb(t_color color)
{
	return (color.r << 16 | color.g << 8 | color.b);
}

// Put pixel to image
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
