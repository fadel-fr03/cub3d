#include "cub3d.h"
#include <stdlib.h>

static int	process_line_for_dimensions(char *line, t_line_data *data)
{
	int	len;

	trim_trailing_whitespace(line);
	len = ft_strlen(line);
	if (len > data->width)
		data->width = len;
	data->height++;
	if (!create_line_node(line, data))
	{
		free(line);
		free_line_list(data->head);
		return (0);
	}
	return (1);
}

int	get_map_dimensions(int fd, t_game *game)
{
	char		*line;
	t_line_data	data;

	data.width = 0;
	data.height = 0;
	data.head = NULL;
	data.tail = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (!process_line_for_dimensions(line, &data))
			return (0);
		line = get_next_line(fd);
	}
	game->map.width = data.width;
	game->map.height = data.height;
	free_line_list(data.head);
	return (data.height > 0);
}

static int	allocate_map(t_game *game)
{
	int	i;

	game->map.grid = malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.grid)
	{
		printf("Error\nMemory allocation failed\n");
		return (0);
	}
	i = 0;
	while (i < game->map.height)
	{
		game->map.grid[i] = malloc(sizeof(char) * (game->map.width + 1));
		if (!game->map.grid[i])
		{
			printf("Error\nMemory allocation failed\n");
			while (--i >= 0)
				free(game->map.grid[i]);
			return (free(game->map.grid), game->map.grid = NULL, 0);
		}
		ft_memset(game->map.grid[i], ' ', game->map.width);
		game->map.grid[i][game->map.width] = '\0';
		i++;
	}
	game->map.grid[game->map.height] = NULL;
	return (1);
}

static int	fill_map(int fd, t_game *game)
{
	char	*line;
	int		y;
	int		x;
	int		len;

	y = -1;
	line = get_next_line(fd);
	while (line && ++y < game->map.height)
	{
		trim_trailing_whitespace(line);
		len = ft_strlen(line);
		x = -1;
		while (++x < len && x < game->map.width)
		{
			if (!is_valid_map_char(line[x]))
				return (printf("Error\nInvalid character '%c' in map\n",
						line[x]), free(line), 0);
			game->map.grid[y][x] = line[x];
		}
		while (x++ < game->map.width)
			game->map.grid[y][x] = ' ';
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

int	parse_map(int fd, t_game *game)
{
	if (!get_map_dimensions(fd, game))
	{
		printf("Error\nEmpty map\n");
		return (0);
	}
	if (!allocate_map(game))
		return (0);
	if (!fill_map(fd, game))
		return (0);
	return (1);
}
