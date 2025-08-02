#include "cub3d.h"

// Initialize MLX and create window
int	init_mlx(t_game *game)
{
	game->mlx.mlx = mlx_init();
	if (!game->mlx.mlx)
	{
		printf("Error\nFailed to initialize MLX\n");
		return (0);
	}
	game->mlx.win = mlx_new_window(game->mlx.mlx, WIN_WIDTH,
			WIN_HEIGHT, "cub3D");
	if (!game->mlx.win)
	{
		printf("Error\nFailed to create window\n");
		return (0);
	}
	game->mlx.img = mlx_new_image(game->mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->mlx.img)
	{
		printf("Error\nFailed to create image\n");
		return (0);
	}
	game->mlx.addr = mlx_get_data_addr(game->mlx.img,
			&game->mlx.bits_per_pixel,
			&game->mlx.line_length,
			&game->mlx.endian);
	return (1);
}

// Load a single texture
static int	load_texture(t_game *game, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx.mlx, path,
			&texture->width, &texture->height);
	if (!texture->img)
	{
		printf("Error\nFailed to load texture: %s\n", path);
		return (0);
	}
	texture->addr = mlx_get_data_addr(texture->img,
			&texture->bits_per_pixel,
			&texture->line_length,
			&texture->endian);
	return (1);
}

// Load all textures
int	load_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!load_texture(game, &game->textures[i],
				game->texture_paths[i]))
			return (0);
		i++;
	}
	return (1);
}
