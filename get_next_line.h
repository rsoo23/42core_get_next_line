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

#include <stdlib.h> // malloc, free
#include <unistd.h> // read, close
// testing
#include <stdio.h>
#include <fcntl.h>  // open

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

// get_next_line.c
char	*get_next_line(int fd);
char	*read_buffer_assign(int fd, char *buffer, int *read_status);
char	*assign_line(char *buffer, char *line);
// get_next_line_utils.c
int     line_len(char *buffer, int position);

#endif