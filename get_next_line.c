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

static char	*strjoin_free(char *free_str, char *str)
{
	char	*temp;

	temp = ft_strjoin(free_str, str);
	free(free_str);
	return (temp);
}

static char	*eol_trim(char *line, int start, int end)
{
	char	*trimmed_line;
	int		count;

	count = 0;
	trimmed_line = malloc(end - start + 1);
	if (!trimmed_line)
		return (NULL);
	if (start > 0)
		end--;
	while (start + count <= end)
	{
		trimmed_line[count] = line[start + count];
		count++;
	}
	trimmed_line[count] = '\0';
	if (start > 0)
		free(line);
	return (trimmed_line);
}

static char	*read_buffer_assign(int fd, char *line)
{
	char	*buffer;
	ssize_t	read_num;

	read_num = 1;
	if (!line)
		line = malloc(1);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer || !line)
		return (NULL);
	while (read_num > 0)
	{
		read_num = read(fd, buffer, BUFFER_SIZE);
		if (read_num == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_num] = '\0';
		// printf("read:%ld, buffer:%s\n", read_num, buffer);
		if (find_nl_null_pos(buffer, BUFFER_SIZE) >= 0)
			read_num = -1;
		line = strjoin_free(line, buffer);
	}
	free(buffer);
	// printf("line: %s\n", line);
	return(line);
}


char	*get_next_line(int fd)
{
	static char	*eol_buf;
	char		*line;
	int			nl_pos;
	int			line_len;

	if (BUFFER_SIZE < 0 || fd < 0)
		return (NULL);
	nl_pos = -1;
	line_len = 0;
	eol_buf = read_buffer_assign(fd, eol_buf);
	// printf("line before trim: %s\n", eol_buf);
	line_len = ft_strlen(eol_buf);
	nl_pos = find_nl_null_pos(eol_buf, line_len);
	if (nl_pos >= 0)
	{
		line = eol_trim(eol_buf, 0, nl_pos);	
		eol_buf = eol_trim(eol_buf, nl_pos + 1, line_len);
		// printf("eolbuf: %s\n", eol_buf);
		return(line);
	}
	return(eol_buf);
}

// read_buffer_assign: 
// creates the line (in multiples of the buffer) until \n or \0 is found

// strjoin(eol_buf, line):
// joins any excess strings from the previous line to the created line

// eol_trim:
// takes the resulting line and trims it for any excess string
// (anything after \n) stores it in eol_buf for access in the next gnl call

int	main()
{
	int	fd = open("file.txt", O_RDONLY);

	if (fd == -1)
		return(1);
	// get_next_line(fd);
	// get_next_line(fd);
	// get_next_line(fd);
	printf("1: %s", get_next_line(fd));
	printf("2: %s", get_next_line(fd));
	printf("3: %s", get_next_line(fd));
	printf("4: %s", get_next_line(fd));
	close(fd);
}

// cc -Wall -Wextra -Werror -D BUFFER_SIZE=4 *.c && ./a.out

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
