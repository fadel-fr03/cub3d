#include "cub3d.h"

// Free texture paths
static void	free_texture_paths(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->texture_paths[i])
		{
			free(game->texture_paths[i]);
			game->texture_paths[i] = NULL;
		}
		i++;
	}
}

// Destroy textures
static void	destroy_textures(t_game *game)
{
	int	i;

	if (!game->mlx.mlx)
		return ;
	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img)
		{
			mlx_destroy_image(game->mlx.mlx, game->textures[i].img);
			game->textures[i].img = NULL;
		}
		i++;
	}
}

static void	destroy_mlx(t_game *game)
{
	if (!game->mlx.mlx)
		return ;
	if (game->mlx.img)
	{
		mlx_destroy_image(game->mlx.mlx, game->mlx.img);
		game->mlx.img = NULL;
	}
	if (game->mlx.win)
	{
		mlx_destroy_window(game->mlx.mlx, game->mlx.win);
		game->mlx.win = NULL;
	}
	mlx_destroy_display(game->mlx.mlx);
	free(game->mlx.mlx);
	game->mlx.mlx = NULL;
}

// Main cleanup function
void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	free_texture_paths(game);
	if (game->map.grid)
	{
		free_map(game->map.grid);
		game->map.grid = NULL;
	}
	destroy_textures(game);
	destroy_mlx(game);
}
