/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:01:10 by rsoo              #+#    #+#             */
/*   Updated: 2023/04/30 17:01:10 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	line_len(char *buffer, int position)
{
	int	line_len;

	line_len = 1;
	while (buffer[position] != '\n')
	{
		line_len++;
		position++;
	}
	return (line_len);
}
