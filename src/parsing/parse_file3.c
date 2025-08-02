#include "cub3d.h"

static int	parse_map_from_lines(t_mapline *lines, t_game *game)
{
	t_grid_context	ctx;

	ctx.dims = calculate_map_dimensions(lines);
	game->map.width = ctx.dims.width;
	game->map.height = ctx.dims.height;
	game->map.grid = malloc(sizeof(char *) * (ctx.dims.height + 1));
	if (!game->map.grid)
		return (0);
	ctx.grid = game->map.grid;
	ctx.lines = lines;
	if (!allocate_and_fill_grid(&ctx))
	{
		game->map.grid = NULL;
		return (0);
	}
	return (1);
}

static int	append_mapline(t_parse_ctx *ctx, char *line)
{
	if (!add_mapline(&ctx->head, &ctx->tail, line))
	{
		free(line);
		free_maplines(ctx->head);
		return (0);
	}
	return (1);
}

static int	handle_pre_map_line(t_parse_ctx *ctx, char *line)
{
	int	ret;

	ret = process_line(line, ctx->game);
	if (ret == 0)
	{
		free(line);
		free_maplines(ctx->head);
		return (0);
	}
	if (ret == 2)
	{
		ctx->map_started = 1;
		if (!append_mapline(ctx, line))
			return (0);
	}
	return (1);
}

int	finalize_map_parse(t_parse_ctx *ctx)
{
	int	ret;

	ret = parse_map_from_lines(ctx->head, ctx->game);
	free_maplines(ctx->head);
	if (!ret)
		return (0);
	return (1);
}

int	read_file_loop(int fd, t_parse_ctx *ctx)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (!ctx->map_started)
		{
			if (!handle_pre_map_line(ctx, line))
				return (0);
		}
		else
		{
			if (!append_mapline(ctx, line))
				return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}
