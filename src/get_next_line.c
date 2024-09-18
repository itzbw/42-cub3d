/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwong <bwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 19:24:32 by bwong             #+#    #+#             */
/*   Updated: 2023/08/28 15:11:20 by ctchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*ft_realloc(size_t count, char *line, int size)
{
	char	*new;

	new = malloc(sizeof(*new) * (count + size + 1));
	if (!new)
		return (NULL);
	new[count + size] = '\0';
	if (size > 0)
		ft_memcpy(new, line, size);
	free(line);
	return (new);
}

int	str_joint(char *buf, char **line, int *i, int *len)
{
	int		temp;
	int		size;

	temp = *i;
	size = ft_strlen(*line);
	while (buf[*i] != '\n' && buf[*i] != '\0')
		*i = *i + 1;
	*line = ft_realloc((*i - temp), *line, size);
	if (*line == NULL)
		return (-1);
	while (temp < *i)
	{
		(*line)[size] = buf[temp];
		temp++;
		size++;
		*len = *len - 1;
	}
	if (buf[*i] == '\n')
	{
		*len = *len - 1;
		*i = *i + 1;
		return (1);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static int	i;
	int			temp;
	static int	len;
	static char	buf[BUFFER_SIZE + 1];

	*line = malloc(sizeof(char *));
	if (!*line)
		return (-1);
	(*line)[0] = '\0';
	while (i == 0 || len >= 0)
	{
		if (i == 0 || len == 0)
		{
			len = read(fd, buf, BUFFER_SIZE);
			if (len == -1)
				return (-1);
			buf[len] = '\0';
			i = 0;
		}
		if (len == 0)
			return (0);
		temp = str_joint(buf, line, &i, &len);
		return (temp);
	}
	return (-1);
}
