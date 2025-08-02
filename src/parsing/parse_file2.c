#include "cub3d.h"

t_map_dims	calculate_map_dimensions(t_mapline *lines)
{
	t_mapline	*current;
	t_map_dims	dims;
	int			len;

	dims.height = 0;
	dims.width = 0;
	current = lines;
	while (current)
	{
		len = get_line_length(current->line);
		if (len > dims.width)
			dims.width = len;
		dims.height++;
		current = current->next;
	}
	return (dims);
}

static void	cleanup_grid(char **grid, int rows)
{
	while (--rows >= 0)
		free(grid[rows]);
	free(grid);
}

static int	validate_and_copy_char(char c, char **grid, int x, int y)
{
	if (c != '\n' && c != '\r')
	{
		if (!is_valid_map_char(c))
		{
			printf("Error\nInvalid character '%c' in map\n", c);
			return (0);
		}
		grid[y][x] = c;
	}
	return (1);
}

static int	fill_grid_row(t_mapline *line, char **grid, int y, int width)
{
	int	x;

	ft_memset(grid[y], ' ', width);
	grid[y][width] = '\0';
	x = 0;
	while (line->line[x] && x < width)
	{
		if (!validate_and_copy_char(line->line[x], grid, x, y))
		{
			cleanup_grid(grid, y + 1);
			return (0);
		}
		x++;
	}
	return (1);
}

int	allocate_and_fill_grid(t_grid_context *ctx)
{
	t_mapline	*current;
	int			y;

	y = 0;
	current = ctx->lines;
	while (current && y < ctx->dims.height)
	{
		ctx->grid[y] = malloc(sizeof(char) * (ctx->dims.width + 1));
		if (!ctx->grid[y])
		{
			cleanup_grid(ctx->grid, y);
			return (0);
		}
		if (!fill_grid_row(current, ctx->grid, y, ctx->dims.width))
			return (0);
		y++;
		current = current->next;
	}
	ctx->grid[ctx->dims.height] = NULL;
	return (1);
}
