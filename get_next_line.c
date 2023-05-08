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

char	*read_buffer_assign(int fd, char *line)
{
	char	*buffer;
	ssize_t	read_num;

	read_num = 1;
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	while (read_num > 0)
	{
		read_num = read(fd, buffer, BUFFER_SIZE);
		// printf("read:%ld, buffer:%s\n", read_num, buffer);
		if (read_num == -1 || buffer[0] == '\0')
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_num] = '\0';
		line = ft_strjoin(line, buffer);
		if (ft_strchr(buffer, '\n') >= 0)
			break ;
	}
	free(buffer);
	return (line);
}

static char *get_trimmed_line(char *unt_l)
{
	size_t	len;
	char	*trm_l;

	len = 0;
	while (unt_l && unt_l[len] != '\n')
		len++;
	trm_l = ft_calloc(len + 2, sizeof(char));
	if (!trm_l)
		return (NULL);
	len = 0;
	while (unt_l[len] && unt_l[len] != '\n')
	{
		trm_l[len] = unt_l[len];
		len++;
	}
	if (unt_l && unt_l[len] == '\n')
		trm_l[len++] = '\n';
	trm_l[len] = '\0';
	return (trm_l);
}

static char *get_eol_buf(char *unt_l, char *buf)
{
	size_t	len;
	size_t	buf_count;

	len = 0;
	buf_count = 0;
	while (unt_l && unt_l[len] != '\n')
		len++;
	len++;
	if (unt_l[len] == '\0')
		return (NULL);
	buf = ft_calloc(ft_strlen(unt_l) - len + 1, sizeof(char));
	if (!buf)
		return (NULL);
	while (unt_l[len])
		buf[buf_count++] = unt_l[len++];
	buf[buf_count] = '\0';
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*eol_buf;
	char		*untrimmed_line;
	char		*trimmed_line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	untrimmed_line = read_buffer_assign(fd, eol_buf);
	if (!untrimmed_line)
		return (NULL);
	if (ft_strchr(untrimmed_line, '\n') >= 0)
	{
		trimmed_line = get_trimmed_line(untrimmed_line);
		eol_buf = get_eol_buf(untrimmed_line, eol_buf);
		// printf("eol_buf: %s\n\n", eol_buf);
		free(untrimmed_line);
		return(trimmed_line);
	}
	return(untrimmed_line);
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
