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

int	ft_find_newline_pos(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
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
	int		len;
	int		nl_pos;
	char	*trimmed_line;

	len = -1;
	if (!ft_strlen(untrimmed_line))
		return (NULL);
	nl_pos = ft_find_newline_pos(untrimmed_line);
	if (nl_pos == -1)
	{
		trimmed_line = ft_strdup(untrimmed_line);
		return (trimmed_line);
	}
	trimmed_line = malloc((nl_pos + 2) * sizeof(char));
	if (!trimmed_line)
		return (ft_free_ret_null(trimmed_line));
	while (len++ <= nl_pos)
		trimmed_line[len] = untrimmed_line[len];
	trimmed_line[len - 1] = '\0';
	return (trimmed_line);
}

char	*get_endofline_buf(char *buf)
{
	size_t	buf_count;
	int		nl_pos;
	char	*trimmed_buf;

	buf_count = 0;
	if (!buf)
		return (ft_free_ret_null(buf));
	nl_pos = ft_find_newline_pos(buf);
	if (nl_pos == -1)
		return (ft_free_ret_null(buf));
	trimmed_buf = malloc((ft_strlen(buf) - nl_pos) * sizeof(char));
	if (!trimmed_buf)
		return (ft_free_ret_null(trimmed_buf));
	nl_pos++;
	while (buf[nl_pos])
		trimmed_buf[buf_count++] = buf[nl_pos++];
	trimmed_buf[buf_count] = '\0';
	free(buf);
	return (trimmed_buf);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dest;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
