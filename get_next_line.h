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
// get_next_line_utils.c
int     ft_strchr(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
size_t  ft_strlen(const char *s);
void	*ft_calloc(size_t n_elem, size_t size);
void	ft_bzero(void *s, size_t n);

#endif
