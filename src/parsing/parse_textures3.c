#include "cub3d.h"

static int	validate_color_input(char *trimmed)
{
	int	len;

	len = ft_strlen(trimmed);
	if (len == 0 || !*trimmed)
	{
		printf("Error\nMissing color values\n");
		return (0);
	}
	return (1);
}

int	parse_colors(char *line, t_game *game)
{
	char	*trimmed;
	t_color	*target_color;

	trimmed = skip_spaces(line);
	target_color = get_target_color(trimmed, game);
	if (!target_color)
		return (0);
	if (target_color->r != -1)
		return (printf("Error\nDuplicate color definition\n"), 0);
	trimmed += 2;
	trimmed = skip_spaces(trimmed);
	trim_color_line(trimmed);
	if (!validate_color_input(trimmed))
		return (0);
	if (!parse_rgb(trimmed, target_color))
		return (printf("Error\nInvalid color format. Use R,G,B (0-255)\n"), 0);
	return (1);
}
