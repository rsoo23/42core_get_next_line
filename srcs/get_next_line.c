/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:13:14 by rsoo              #+#    #+#             */
/*   Updated: 2023/04/30 15:13:14 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*get_next_line(int fd)
{
	char			*line;
	static ssize_t	read_num;
	static char		*buffer;
	static int		position;
	int				line_count;

	line = NULL;
	line_count = 0;
	if (!buffer)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (NULL);
		read_num = read(fd, buffer, BUFFER_SIZE);
		if (read_num == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_num] = '\0';
	}

	if (read_num == 0)
	{
		free(buffer);
		return(NULL);
	}

	line = malloc(ft_line_len(buffer, position) + 1);
	if (!line)
		return (NULL);

	while (buffer[position] != '\n' && buffer)
		line[line_count++] = buffer[position++];
	if (buffer[position] == '\n')
	{
		buffer[position] = '\n';
		buffer[position + 1] = '\0';
	}
	else
		read_num = 0;
	return (line);
}

// read_num == 0: EOF is reached

int	main()
{
	int		fd = open("file.txt", O_RDONLY);
	char	*line;

	if (fd == -1)
		return(1);

	line = get_next_line(fd);
	printf("%s", line);
	close(fd);
}
