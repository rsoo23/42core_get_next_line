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

// char	*assign_temp_eol(char *line, char *buffer)
// {
// 	int		count;
// 	char	*temp;

// 	count = 0;
// 	while (buffer[count] != '\n')
// 		count++;
// 	printf("%d\n", count);
// 	temp = malloc(count + 2);
// 	if (!temp)
// 		return (NULL);
// 	temp[count + 1] = '\0';
// 	temp[count] = '\n';
// 	while (count >= 1)
// 	{
// 		temp[count - 1] = buffer[count - 1];
// 		count--;
// 	}
// 	line = ft_strjoin(line, temp);
// 	free(temp);
// 	return (line);
// }

char	*assign_temp_eof(char *line, char *buffer)
{
	int		count;
	char	*temp;

	count = 0;
	while (buffer[count])
		count++;
	temp = malloc(count + 1);
	if (!temp)
		return (NULL);
	temp[count] = '\0';
	while (count >= 1)
	{
		temp[count - 1] = buffer[count - 1];
		count--;
	}
	line = ft_strjoin(line, temp);
	free(temp);
	return (line);
}

char	*line_cat(char *line, char *buffer, int *end_gnl)
{
	if (ft_strchr_pos(buffer, '\0'))
	{
		*end_gnl = 1;
		line = assign_temp_eof(line, buffer);
	}
	else
		line = ft_strjoin(line, buffer);
	return (line);
}

char	*read_buffer_assign(int fd, char *line)
{
	char	*buffer;
	int		end_gnl;
	ssize_t	read_num;

	read_num = -1;
	end_gnl = 0;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!end_gnl)
	{
		read_num = read(fd, buffer, BUFFER_SIZE);
		if (read_num == -1 || read_num == 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_num] = '\0';
		line = line_cat(line, buffer, &end_gnl);
	}
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;

	line = NULL;
	if (BUFFER_SIZE < 0 || fd < 0)
		return (NULL);
	line = read_buffer_assign(fd, line);
	return (line);
}

// read_num == 0: EOF is reached

int	main()
{
	int		fd = open("file.txt", O_RDONLY);

	if (fd == -1)
		return(1);
	printf("%s", get_next_line(fd));
	close(fd);
}

//File Content:
// This is line one.\n
// What is love?

// Buffers: (ex: 4)
// First call = [This][ is ][line][ one][.\nWh]
// Line1 =      [This is line one.\nWh]
// return line  [This is line one.\n]
// extra buffer [Wh]

// Second call = [at i][s lo][ve?\0]
// Line2 =       [Wh]+[at i]+[s lo]+[ve?\0]

