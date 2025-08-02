#include "cub3d.h"

int	read_and_parse_file(int fd, t_game *game)
{
	t_parse_ctx	ctx;
	int			ret;

	ctx.map_started = 0;
	ctx.head = NULL;
	ctx.tail = NULL;
	ctx.game = game;
	ret = read_file_loop(fd, &ctx);
	if (!ret)
		return (0);
	if (ctx.head)
		return (finalize_map_parse(&ctx));
	return (1);
}

// Main parsing function
int	parse_cub_file(char *filename, t_game *game)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCannot open file: %s\n", strerror(errno));
		return (0);
	}
	if (!read_and_parse_file(fd, game))
	{
		close(fd);
		return (0);
	}
	close(fd);
	if (!check_elements(game))
		return (0);
	if (!validate_map(game))
		return (0);
	init_player_direction(game);
	return (1);
}
