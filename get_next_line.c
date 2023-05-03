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

char	*line_cat(char *line, char *buffer, int *end_gnl)
{
	if (ft_strchr_pos(buffer, '\0', BUFFER_SIZE) >= 0)
		*end_gnl = 1;
	else if (ft_strchr_pos(buffer, '\n', BUFFER_SIZE) >= 0)
		*end_gnl = 1;
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
		printf("read:%ld, buffer:%s\n", read_num, buffer);
		buffer[read_num] = '\0';
		line = line_cat(line, buffer, &end_gnl);
	}
	free(buffer);	
	return (line);
}

char	*eol_trim(char *line, size_t start, size_t end)
{
	char	*trimmed_line;
	int		count;

	trimmed_line = malloc(end - start + 1);
	if (!trimmed_line)
		return (NULL);
	count = 0;
	if (start > 0)
		end--;
	while (start + count <= end)
	{
		trimmed_line[count] = line[start + count];
		count++;
	}
	trimmed_line[count] = '\0';
	return (trimmed_line);
}

//  01234567890123456 789 
// [This is line one.\nWh]
// [                   ]
// start = 0, end = 17

char	*get_next_line(int fd)
{
	char		*line;
	static char	*eol_buf;
	size_t		nl_pos;
	size_t		line_len;

	nl_pos = -1;
	line_len = 0;
	line = malloc(1);
	if (!eol_buf)
		eol_buf = malloc(1);
	if (BUFFER_SIZE < 0 || fd < 0)
		return (NULL);
	line = read_buffer_assign(fd, line);

	line_len = ft_strlen(line);
	
	line = ft_strjoin(eol_buf, line);
	
	nl_pos = ft_strchr_pos(line, '\n', line_len);
	if (nl_pos > 0 && nl_pos != line_len - 1)
	{
		eol_buf = eol_trim(line, nl_pos + 1, line_len);
		line = eol_trim(line, 0, nl_pos);	
		printf("l:%s, b:%s\n", line, eol_buf);
	}
	return (line);
}

// read_buffer_assign: 
// creates the line (in multiples of the buffer) until \n or \0 is found

// strjoin(eol_buf, line):
// joins any excess strings from the previous line to the created line

// eol_trim:
// takes the resulting line and trims it for any excess string (anything after \n)
// stores it in eol_buf for access in the next gnl call

int	main()
{
	int	fd = open("file.txt", O_RDONLY);

	if (fd == -1)
		return(1);
	// get_next_line(fd);
	// get_next_line(fd);
	// get_next_line(fd);
	printf("%s", get_next_line(fd));
	printf("\n");
	printf("%s", get_next_line(fd));
	printf("\n");
	printf("%s", get_next_line(fd));
	close(fd);
}

//File Content:
// This is line one.\n
// What is love?

// [This ][is li][ne on][e.\nWh]
// [this i][s line][ one.\n]

// BUFFER_SIZE=4
// First call = [This][ is ][line][ one][.\nWh]
// Line1 =      [This is line one.\nWh]
// return line  [This is line one.\n]
// extra buffer [Wh]

// Second call = [at i][s lo][ve?\n]
// Line2 =       [Wh]+[at i]+[s lo]+[ve?\n]
// return line  [This is line one.\n]
// extra buffer []

// Third call = [This][ als][o th][e th][ird ][line][.\nCo]
// Line2 =       [Wh]+[at i]+[s lo]+[ve?\n]
// return line  [This is line one.\n]
// extra buffer []
