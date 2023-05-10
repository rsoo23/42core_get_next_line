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

char	*get_next_line(int fd)
{
	static char	*endofline_buf;
	char		*trimmed_line;
	char		*buffer;
	int			read_num;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	read_num = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (!ft_newline_in_str(endofline_buf))
	{
		read_num = read(fd, buffer, BUFFER_SIZE);
		if (read_num <= 0)
			break ;
		buffer[read_num] = '\0';
		//printf("eolbuf: %s, count: %d", endofline_buf, count);
		endofline_buf = ft_strjoin(endofline_buf, buffer);
	}
	free(buffer);
	if (read_num == -1)
		return (NULL);
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
