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

int	ft_newline_in_str(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char			*res;
	unsigned int	i;
	size_t			len1;
	size_t			len2;

	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = malloc(len1 + len2 + 1);
	if (!res)
		return (NULL);
	while (i++ < len1)
		res[i - 1] = s1[i - 1];
	i = 0;
	while (i++ < len2)
		res[i - 1 + len1] = s2[i - 1];
	res[i - 1 + len1] = '\0';
	free((char *)s1);
	return (res);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*get_trimmed_line(char *untrimmed_line)
{
	size_t	len;
	char	*trimmed_line;

	len = 0;
	if (!ft_strlen(untrimmed_line))
		return (NULL);
	while (untrimmed_line[len] && untrimmed_line[len] != '\n')
		len++;
	trimmed_line = malloc((len + 2) * sizeof(char));
	if (!trimmed_line)
		return (NULL);
	len = 0;
	while (untrimmed_line[len] && untrimmed_line[len] != '\n')
	{
		trimmed_line[len] = untrimmed_line[len];
		len++;
	}
	if (untrimmed_line[len] && untrimmed_line[len] == '\n')
		trimmed_line[len++] = '\n';
	trimmed_line[len] = '\0';
	return (trimmed_line);
}

char	*get_endofline_buf(char *buf)
{
	size_t	len;
	size_t	buf_count;
	char	*trimmed_buf;

	len = 0;
	buf_count = 0;
	if (!buf)
		return (ft_free_ret_null(buf));
	while (buf[len] && buf[len] != '\n')
		len++;
	len++;
	if (buf[len] == '\0')
		return (ft_free_ret_null(buf));
	trimmed_buf = malloc((ft_strlen(buf) - len + 1) * sizeof(char));
	if (!trimmed_buf)
		return (NULL);
	while (buf[len])
		trimmed_buf[buf_count++] = buf[len++];
	trimmed_buf[buf_count] = '\0';
	return (trimmed_buf);
}
