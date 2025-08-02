#include "cub3d.h"

int	parse_textures(char *line, t_game *game)
{
	char	*trimmed;
	int		tex_index;

	trimmed = skip_spaces(line);
	tex_index = get_texture_index(trimmed);
	if (tex_index == -1)
		return (0);
	if (game->texture_paths[tex_index])
		return (printf("Error\nDuplicate texture definition\n"), 0);
	trimmed += 3;
	trimmed = skip_spaces(trimmed);
	trim_line_end(trimmed);
	if (!validate_texture_file(trimmed))
		return (0);
	game->texture_paths[tex_index] = ft_strdup(trimmed);
	if (!game->texture_paths[tex_index])
		return (printf("Error\nMemory allocation failed\n"), 0);
	return (1);
}

// Parse color value (0-255)
static int	parse_color_value(char *str, int *value)
{
	int	i;
	int	num;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (!str[i])
		return (0);
	if (!ft_isdigit(str[i]))
		return (0);
	num = ft_atoi(str + i);
	if (num < 0 || num > 255)
		return (0);
	*value = num;
	return (1);
}

// Parse RGB color
int	parse_rgb(char *str, t_color *color)
{
	char	**split;
	int		ret;

	split = ft_split(str, ',');
	if (!split)
	{
		printf("Error\nMemory allocation failed\n");
		return (0);
	}
	if (count_split_elements(split) != 3)
	{
		free_split(split);
		return (0);
	}
	ret = 1;
	if (!parse_color_value(split[0], &color->r)
		|| !parse_color_value(split[1], &color->g)
		|| !parse_color_value(split[2], &color->b))
		ret = 0;
	free_split(split);
	return (ret);
}

t_color	*get_target_color(char *trimmed, t_game *game)
{
	if (ft_strncmp(trimmed, "F ", 2) == 0)
		return (&game->floor_color);
	else if (ft_strncmp(trimmed, "C ", 2) == 0)
		return (&game->ceiling_color);
	return (NULL);
}

void	trim_color_line(char *trimmed)
{
	int	len;

	len = ft_strlen(trimmed);
	while (len > 0 && (trimmed[len - 1] == '\n' || trimmed[len - 1] == '\r'
			|| trimmed[len - 1] == ' ' || trimmed[len - 1] == '\t'))
	{
		trimmed[len - 1] = '\0';
		len--;
	}
}
