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

// int main()
// {
// 	printf("%d", find_nl_null_pos("This_is_line_one.123\nWh", '\n'));
// }

int	find_nl_null_pos(char *s, int len)
{
	int	count;

	count = 0;
	while (count < len)
	{
		if (s[count] == '\0' || s[count] == '\n')
			return (count);
		count++;
	}
	return (-1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*res;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (0);
	while (s1[i])
		res[j++] = s1[i++];
	i = 0;
	while (s2[i])
		res[j++] = s2[i++];
	res[j] = '\0';
	return (res);
}

int	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
