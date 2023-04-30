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

// get_next_line.c
char			*get_next_line(int fd);
// get_next_line_utils.c
unsigned int	ft_line_len(char *buffer, int position);

#endif