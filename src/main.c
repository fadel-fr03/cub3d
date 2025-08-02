#include "cub3d.h"
#include "bonus.h"

static void	init_game(t_game *game)
{
	int	i;

	ft_bzero(game, sizeof(t_game));
	game->floor_color.r = -1;
	game->floor_color.g = -1;
	game->floor_color.b = -1;
	game->ceiling_color.r = -1;
	game->ceiling_color.g = -1;
	game->ceiling_color.b = -1;
	i = 0;
	while (i < 4)
	{
		game->texture_paths[i] = NULL;
		i++;
	}
	i = 0;
	while (i < 6)
	{
		game->keys[i] = 0;
		i++;
	}
}

static int	check_file_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

int	game_loop(t_game *game)
{
	handle_movement(game);
	ft_bzero(game->mlx.addr,
		WIN_WIDTH * WIN_HEIGHT * (game->mlx.bits_per_pixel / 8));
	raycaster(game);
	if (USE_BONUS)
		draw_minimap(game);
	mlx_put_image_to_window(game->mlx.mlx,
		game->mlx.win, game->mlx.img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (printf("Error\nUsage: ./cub3D <map.cub>\n"), 1);
	if (!check_file_extension(argv[1]))
	{
		printf("Error\nInvalid file extension. Use .cub files only\n");
		return (1);
	}
	init_game(&game);
	if (!parse_cub_file(argv[1], &game) || !init_mlx(&game)
		|| !load_textures(&game))
	{
		cleanup_game(&game);
		return (1);
	}
	mlx_hook(game.mlx.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.mlx.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.mlx.win, 17, 0, close_window, &game);
	if (USE_BONUS)
		mlx_hook(game.mlx.win, 6, 1L << 6, mouse_move, &game);
	mlx_loop_hook(game.mlx.mlx, game_loop, &game);
	mlx_loop(game.mlx.mlx);
	return (0);
}
