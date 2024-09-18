/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwong <bwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 19:24:35 by bwong             #+#    #+#             */
/*   Updated: 2023/08/28 16:40:08 by ctchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	find_map_size(t_data *data, int i)
{
	int	x;
	int	len;

	x = 0;
	len = 0;
	data->map.buff = ft_split(data->map.tmp, '\n');
	if (!(data->map.buff))
		error_msg("Error\nMap Invalid (Split)");
	free(data->map.tmp);
	while (data->map.buff[i])
	{
		len = ft_strlen(data->map.buff[i]);
		if (x < len)
			x = len;
		i++;
	}
	data->map.width_count = x;
	data->map.height_count = i;
	if (i <= 1)
	{
		free_tex_line(data);
		ft_free_2d(data->map.buff);
		printf("Error\nMap Invalid(height count)");
		exit (1);
	}
}

static void	create_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	find_map_size(data, 0);
	data->map.map = malloc(sizeof(char *) * (data->map.height_count + 1));
	if (!(data->map.map))
		error_msg("Error\nMalloc failed");
	data->map.map[data->map.height_count] = NULL;
	while (data->map.buff[i])
	{
		data->map.map[i] = malloc(sizeof(char) * (data->map.width_count + 1));
		if (!(data->map.map[i]))
			error_msg("Error\nMalloc failed");
		j = 0;
		while (j < data->map.width_count)
		{
			data->map.map[i][j] = ' ';
			j++;
		}
		data->map.map[i][data->map.width_count] = '\0';
		i++;
	}
}

static void	fill_map(t_data *data)
{
	int		i;
	size_t	j;

	i = 0;
	while (data->map.map[i])
	{
		j = 0;
		while (j < ft_strlen(data->map.buff[i]))
		{
			if (!map_component_check(&data->map.buff[i][j])
				&& data->map.buff[i][j] != '\0')
				free_fill_map(data);
			data->map.map[i][j] = data->map.buff[i][j];
			if (str_check(data->map.map[i][j], "NSEW") == 1)
			{
				data->pl.pcount++;
				data->pl.posx = j;
				data->pl.posy = i;
			}
			j++;
		}
		i++;
	}
	ft_free_2d(data->map.buff);
}

static char	*tmp_map(char *first_map_line, char *line)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin(line, "\n");
	tmp2 = ft_strjoin(first_map_line, tmp1);
	if (*first_map_line && first_map_line)
	{
		free(first_map_line);
		first_map_line = NULL;
	}
	free(tmp1);
	return (tmp2);
}

void	read_map(t_data *data, char *line)
{
	data->map.tmp = ft_strjoin(line, "\n");
	while ((get_next_line(data->fd, &line) > 0))
	{
		if (line[0] == '\0' || line_empty_check(line) == 1)
		{
			free(line);
			free_tex_line(data);
			free(data->map.tmp);
			error_msg("Error\nEmpty line in the map");
		}
		data->map.tmp = tmp_map(data->map.tmp, line);
		free(line);
	}
	free(line);
	close(data->fd);
	create_map(data);
	fill_map(data);
}
