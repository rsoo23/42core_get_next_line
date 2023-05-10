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

char	*read_buffer_assign(int fd, char *endofline_buf)
{
	int		read_num;
	char	*buffer;

	read_num = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (ft_find_newline_pos(endofline_buf) == -1)
	{
		read_num = read(fd, buffer, BUFFER_SIZE);
		if (read_num <= 0)
			break ;
		buffer[read_num] = '\0';
		endofline_buf = ft_strjoin(endofline_buf, buffer);
	}
	free(buffer);
	if (read_num == -1)
		return (NULL);
	return (endofline_buf);
}

char	*get_next_line(int fd)
{
	static char	*endofline_buf;
	char		*trimmed_line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	endofline_buf = read_buffer_assign(fd, endofline_buf);
	trimmed_line = get_trimmed_line(endofline_buf);
	endofline_buf = get_endofline_buf(endofline_buf);
	return (trimmed_line);
}

char	*ft_free_ret_null(char *free_str)
{
	free(free_str);
	free_str = NULL;
	return (NULL);
}

// int	main()
// {
// 	int	fd = open("file.txt", O_RDONLY);

// 	if (fd == -1)
// 		return(1);
// 	printf("1: %s", get_next_line(fd));
// 	printf("2: %s", get_next_line(fd));
// 	printf("3: %s", get_next_line(fd));
// 	printf("4: %s", get_next_line(fd));
// 	close(fd);
// }

// cc -Wall -Wextra -Werror -D BUFFER_SIZE=4 *.c && ./a.out
