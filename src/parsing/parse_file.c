#include "cub3d.h"

void	free_maplines(t_mapline *head)
{
	t_mapline	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->line);
		free(tmp);
	}
}

// Add a line to the map lines list
int	add_mapline(t_mapline **head, t_mapline **tail, char *line)
{
	t_mapline	*new;

	new = malloc(sizeof(t_mapline));
	if (!new)
		return (0);
	new->line = ft_strdup(line);
	if (!new->line)
	{
		free(new);
		return (0);
	}
	new->next = NULL;
	if (!*head)
		*head = new;
	else
		(*tail)->next = new;
	*tail = new;
	return (1);
}

// Check if all required elements are present
int	check_elements(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!game->texture_paths[i])
			return (printf("Error\nMissing texture information\n"), 0);
		i++;
	}
	if (game->floor_color.r == -1 || game->floor_color.g == -1
		|| game->floor_color.b == -1)
		return (printf("Error\nMissing floor color information\n"), 0);
	if (game->ceiling_color.r == -1 || game->ceiling_color.g == -1
		|| game->ceiling_color.b == -1)
		return (printf("Error\nMissing ceiling color information\n"), 0);
	if (!game->map.grid)
	{
		printf("Error\nNo map found in file\n");
		return (0);
	}
	return (1);
}

// Process a single line from the file
int	process_line(char *line, t_game *game)
{
	char	*trimmed;

	trimmed = skip_spaces(line);
	if (!*trimmed)
		return (1);
	if (*trimmed == '1' || *trimmed == '0' || *trimmed == ' ')
		return (2);
	if (parse_textures(line, game))
		return (1);
	if (parse_colors(line, game))
		return (1);
	printf("Error\nInvalid line: %s\n", line);
	return (0);
}

int	get_line_length(char *line)
{
	int	len;

	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == ' ' || line[len - 1] == '\t'
			|| line[len - 1] == '\n' || line[len - 1] == '\r'))
		len--;
	return (len);
}
