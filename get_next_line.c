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

#include "get_next_line.h"

// reads the file and assigns it to the buffer
char	*read_buffer_assign(int fd, char *buffer, int *read_status)
{
	ssize_t	read_num;

	read_num = -1;
	buffer = malloc(BUFFER_SIZE * sizeof(char));
	if (!buffer)
		return (NULL);
	read_num = read(fd, buffer, BUFFER_SIZE);
	if (read_num == -1 || read_num == 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[read_num] = '\0';
	*read_status = 1;
	return (buffer);
}

char	*assign_line(char *buffer, char *line)
{
	static int	position;
	int			count;

	count = 0;
	line = malloc(line_len(buffer, position) + 1);
	if (!line)
		return (NULL);
	while (buffer[position] != '\n' && buffer[position] != '\0')
		line[count++] = buffer[position++];
	if (buffer[position] == '\n')
	{
		line[count] = '\n';
		position++;
	}
	else if (buffer[position] == '\0')
		line[count] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*buffer;
	static int		read_status;

	if (BUFFER_SIZE < 0 || fd < 0)
		return (NULL);
	line = NULL;
	if (read_status == 0)
		buffer = read_buffer_assign(fd, buffer, &read_status);
	if (!buffer)
		return (NULL);
	line = assign_line(buffer, line);
	return (line);
}

// read_num == 0: EOF is reached

// int	main()
// {
// 	int		fd = open("file.txt", O_RDONLY);
// 	int		newline_num = 4;

// 	if (fd == -1)
// 		return(1);

// 	while (newline_num + 1 > 0)
// 	{
// 		printf("%s", get_next_line(fd));
// 		newline_num--;
// 	}

// 	close(fd);
// }
