/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:14:31 by rsoo              #+#    #+#             */
/*   Updated: 2023/04/30 15:14:31 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h> // malloc, free
# include <unistd.h> // read, close
# include <stdint.h>
// testing
# include <stdio.h>
# include <fcntl.h>  // open

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

// get_next_line.c
char	*get_next_line(int fd);
char	*read_buffer_assign(int fd, char *line);
char	*line_cat(char *line, char *buffer, int *end_gnl);
char	*eol_trim(char *line, size_t start, size_t end);
// get_next_line_utils.c
int		ft_strchr_pos(char *s, char c, int len);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);

#endif
