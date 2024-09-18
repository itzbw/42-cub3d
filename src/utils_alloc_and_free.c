/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctchen <ctchen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:45:03 by ctchen            #+#    #+#             */
/*   Updated: 2023/08/29 17:46:13 by ctchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_free_data_buf(int **buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		free(buf[i]);
		i++;
	}
	free(buf);
}

void	ft_free_2d(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_tex_line(t_data *data)
{
	free(data->info.tex_path[0]);
	free(data->info.tex_path[1]);
	free(data->info.tex_path[2]);
	free(data->info.tex_path[3]);
	free(data->info.line);
}

void	allocate_map_buffer(t_data *data)
{
	int	i;

	data->buf = ft_calloc(data->info.win_height + 1, sizeof(int **));
	if (!(data->buf))
		error_msg("Error\nBuffer Malloc failed");
	i = 0;
	while (i < data->info.win_height)
	{
		data->buf[i] = ft_calloc(data->info.win_width + 1, sizeof(int *));
		if (!(data->buf[i]))
			error_msg("Error\nBuffer malloc failed");
		i++;
	}
}

void	free_fill_map(t_data *data)
{
	ft_free_2d(data->map.map);
	ft_free_2d(data->map.buff);
	free_tex_line(data);
	error_msg("Error\nInvalid component in the map");
}
