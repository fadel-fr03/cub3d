#include <stdlib.h>
#include "structs.h"
#include "cub3d.h"

void	free_line_list(t_line_node *head)
{
	t_line_node	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->line);
		free(head);
		head = tmp;
	}
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ');
}

void	trim_trailing_whitespace(char *line)
{
	int	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == ' ' || line[len - 1] == '\t'
			|| line[len - 1] == '\n' || line[len - 1] == '\r'))
	{
		line[len - 1] = '\0';
		len--;
	}
}

int	create_line_node(char *line, t_line_data *data)
{
	t_line_node	*new_node;

	new_node = malloc(sizeof(t_line_node));
	if (!new_node)
		return (0);
	new_node->line = line;
	new_node->next = NULL;
	if (!data->head)
		data->head = new_node;
	else
		data->tail->next = new_node;
	data->tail = new_node;
	return (1);
}
