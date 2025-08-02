#include "cub3d.h"

static int	check_xpm_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	if (ft_strncmp(filename + len - 4, ".xpm", 4) != 0)
		return (0);
	return (1);
}

static int	check_file_exists(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	get_texture_index(char *trimmed)
{
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
		return (TEX_NO);
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
		return (TEX_SO);
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
		return (TEX_WE);
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
		return (TEX_EA);
	return (-1);
}

void	trim_line_end(char *trimmed)
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

int	validate_texture_file(char *path)
{
	if (!check_xpm_extension(path))
		return (printf("Error\nTexture file must have"
				".xpm extension: %s\n", path), 0);
	if (!check_file_exists(path))
		return (printf("Error\nTexture file not found or"
				"not readable: %s\n", path), 0);
	return (1);
}
