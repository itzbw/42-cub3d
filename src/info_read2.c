/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_read2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctchen <ctchen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:06:27 by ctchen            #+#    #+#             */
/*   Updated: 2023/08/29 17:45:00 by ctchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	find_color(char *line, int *i, char **rgb, int *color)
{
	int	tmp;
	int	j;

	j = *i;
	while (*i < j + 3)
	{
		if (!rgb[*i] || !if_digit(rgb[*i]))
			return (1);
		tmp = ft_atoi(rgb[*i]);
		if (tmp > 255 || tmp < 0)
			return (2);
		*color = *color * 256 + tmp;
		(*i)++;
	}
	while (line[j] != '\0')
	{
		if (line[j] == ',' && line[j + 1] == '\0')
			return (3);
		j++;
	}
	if (rgb[3])
		return (4);
	return (0);
}

static void	check_color_line(t_data *data, char *line, int *info, int *i)
{
	if ((data->info.flag == *info && data->info.floor_color != -1)
		|| (data->info.flag == *info && data->info.ceiling_color != -1))
		info_read_exit(data, line, "Error\ncolor data line doubled");
	while (if_space(line[*i]) && line[*i])
		(*i)++;
	while (if_upper(line[*i]) && line[*i])
		(*i)++;
	while (if_space(line[*i]) && line[*i])
		(*i)++;
}

int	store_color(int info, t_data *data, char *line)
{
	int		i;
	int		color;
	char	**rgb;
	char	*temp;

	i = 0;
	color = 0;
	check_color_line(data, line, &info, &i);
	rem_space_comma_check(data, line, i, &temp);
	rgb = ft_split(temp, ',');
	if (!rgb)
		info_read_exit(data, line, "Error\nRGB Split Invalid");
	i = 0;
	i = find_color(line, &i, rgb, &color);
	if (i > 0)
		free_find_color(data, line, rgb, temp);
	i = 0;
	if (info == FLOOR)
		data->info.floor_color = color;
	else if (info == CEILING)
		data->info.ceiling_color = color;
	ft_free_2d(rgb);
	free(temp);
	return (info);
}

static void	find_resolution(t_data *data, char *line, int *i)
{
	while (if_upper(line[*i]))
		(*i)++;
	while (if_space(line[*i]))
		(*i)++;
	while (ft_isdigit(line[*i]))
		data->info.win_width = data->info.win_width * 10 + line[(*i)++] - '0';
	while (if_space(line[*i]))
		(*i)++;
	if (ft_isdigit(line[*i]))
	{
		while (ft_isdigit(line[*i]))
			data->info.win_height = data->info.win_height * 10 + line[(*i)++]
				- '0';
	}
	else if (data->info.win_width > 2147483647
		|| data->info.win_height > 2147483647)
		info_read_exit(data, line, "Error\nResolution overflow");
	else
		info_read_exit(data, line, "Error\nResolution invalid");
	if (data->info.win_width < 0 || data->info.win_height < 0)
		info_read_exit(data, line, "Error\nResolution is wrong");
}

int	check_resolution(t_data *data, char *line)
{
	int	i;

	i = 0;
	while (if_space(line[i]) == 1 && line[i])
		i++;
	if (data->info.win_width || data->info.win_height)
		info_read_exit(data, line, "Error\nResolution info doubled");
	find_resolution(data, line, &i);
	if (!data->info.win_width || !data->info.win_height)
		info_read_exit(data, line, "Error\nResolution Data invalid");
	while (if_space(line[i]))
		i++;
	if (line[i] != '\0')
		info_read_exit(data, line, "Error\nResolution Data Invalid! (EOF)");
	return (RESOLUTION);
}
