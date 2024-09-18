/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctchen <ctchen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:55:37 by ctchen            #+#    #+#             */
/*   Updated: 2023/08/28 16:25:16 by ctchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	data_check(t_data *data)
{
	if (data->info.flag == -1)
	{
		free_tex_line(data);
		error_msg("Error\nElement not found");
	}
	if (!data->info.win_width || !data->info.win_height)
	{
		free_tex_line(data);
		error_msg("Error\nResolution data not found");
	}
	if (!data->info.tex_path[TEX_NORTH] || !data->info.tex_path[TEX_SOUTH]
		|| !data->info.tex_path[TEX_EAST] || !data->info.tex_path[TEX_WEST])
	{
		free_tex_line(data);
		error_msg("Error\nTexture data not found");
	}
	if (data->info.floor_color == -1 || data->info.ceiling_color == -1)
	{
		free_tex_line(data);
		error_msg("Error\nColor data not found");
	}
}

int	line_empty_check(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

//pas opti
int	map_component_check(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr("01NSEW ", line[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	check_around(char **map, int y, int x, int ylimit)
{
	if ((x + 1) >= (int)ft_strlen(map[y]) || (y + 1) >= ylimit)
		return (1);
	if ((y > 0 && str_check(map[y - 1][x], " \n") != 0)
		|| ((y + 1) && str_check(map[y + 1][x], " \n") != 0)
		|| ((x - 1) > 0 && str_check(map[y][x - 1], " \n") != 0)
		|| ((x + 1) < (int)ft_strlen(map[y])
			&& str_check(map[y][x + 1], " \n") != 0))
		return (1);
	return (0);
}

int	valid_map(char **map, int ylimit)
{
	int	x;
	int	y;
	int	check_flag;

	x = 0;
	y = 0;
	check_flag = 0;
	while (y < ylimit)
	{
		while (x < (int)ft_strlen(map[y]))
		{
			if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'E'
			|| map[y][x] == 'S' || map[y][x] == 'W')
				check_flag = check_around(map, y, x, ylimit);
			if (check_flag != 0)
			{
				printf("Error\nThe map is not walled\n");
				return (1);
			}
			x++;
		}
		y++;
		x = 0;
	}
	return (0);
}
