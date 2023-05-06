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
	trimmed_line = ft_calloc(end - start + 1, sizeof(char));
	if (start > 0)
		end--;
	while (start + count < end)
	{
		trimmed_line[count] = line[start + count];
		count++;
	}
	trimmed_line[count] = '\0';
	return (trimmed_line);
}

static char	*read_buffer_assign(int fd, char *line)
{
	char	*buffer;
	ssize_t	read_num;

	read_num = 1;
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (read_num > 0)
	{
		read_num = read(fd, buffer, BUFFER_SIZE);
		if (read_num == -1 || buffer[0] == '\0')
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_num] = '\0';
		// printf("read:%ld, buffer:%s\n", read_num, buffer);
		if (ft_strchr(buffer, '\n', BUFFER_SIZE) >= 0)
			read_num = -1;
		if (ft_strchr(buffer, '\0', BUFFER_SIZE) >= 0)
			read_num = -1;
		line = strjoin_free(line, buffer);
	}
	free(buffer);
	// printf("line: %s\n", line);
	return(line);
}

static char *process_line(char **buf, char *unt_l)
{
	int		nl_pos;
	int		line_len;
	char	*out_l;

	nl_pos = -1;
	line_len = 0;
	line_len = ft_strlen(unt_l);
	nl_pos = ft_strchr(unt_l, '\n', line_len);
	if (nl_pos == 0 && unt_l[1] == '\0')
		return (unt_l);
	else if (nl_pos >= 0 && ft_strchr(unt_l, '\0', line_len) == -1)
	{
		*buf = eol_trim(unt_l, nl_pos + 1, line_len);
		out_l = eol_trim(unt_l, 0, nl_pos + 1);
		free(unt_l);
		return (out_l);
		// printf("eolbuf: %s\n", eol_buf);
	}
	return (unt_l);
}

char	*get_next_line(int fd)
{
	static char	*eol_buf;
	char		*untrimmed_line;

	if (!eol_buf)
		eol_buf = ft_calloc(1, sizeof(char));
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	untrimmed_line = read_buffer_assign(fd, eol_buf);
	if (!untrimmed_line)
		return (NULL);
	// printf("line before trim: %s\n", eol_buf);
	return(process_line(&eol_buf, untrimmed_line));
}

// read_buffer_assign: 
// creates the line (in multiples of the buffer) until \n or \0 is found

// strjoin(eol_buf, line):
// joins any excess strings from the previous line to the created line

// eol_trim:
// takes the resulting line and trims it for any excess string
// (anything after \n) stores it in eol_buf for access in the next gnl call

// int	main()
// {
// 	int	fd = open("file.txt", O_RDONLY);

// 	if (fd == -1)
// 		return(1);
// 	// get_next_line(fd);
// 	// get_next_line(fd);
// 	// get_next_line(fd);
// 	printf("1: %s", get_next_line(fd));
// 	printf("2: %s", get_next_line(fd));
// 	printf("3: %s", get_next_line(fd));
// 	printf("4: %s", get_next_line(fd));
// 	printf("5: %s", get_next_line(fd));
// 	printf("6: %s", get_next_line(fd));
// 	close(fd);
// }

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
