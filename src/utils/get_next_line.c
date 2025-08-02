#include "./libft.h"

static char	*ft_read_line(int fd, char *line, char *buff)
{
	int	return_value;

	return_value = 1;
	line = ft_gnl_strjoin(line, buff);
	while (!ft_gnl_strchr(line, '\n') && return_value != 0)
	{
		return_value = read(fd, buff, BUFFER_SIZE);
		if (return_value < 0)
			return (NULL);
		buff[return_value] = '\0';
		line = ft_gnl_strjoin(line, buff);
	}
	if (ft_strchr(line, '\n'))
	{
		buff = ft_get_endline(line, buff);
		line = ft_get_line(line);
	}
	if (line == NULL)
		return (NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buff, 0) == -1)
		return (NULL);
	line = ft_read_line(fd, line, buff);
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}
