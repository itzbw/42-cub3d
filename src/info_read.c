/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwong <bwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 19:24:39 by bwong             #+#    #+#             */
/*   Updated: 2023/08/29 17:42:26 by ctchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	store_texture(int texture, t_data *data, char *line)
{
	int	i;
	int	fd_tex;

	i = 0;
	fd_tex = 0;
	if (data->info.tex_path[texture] != NULL)
		info_read_exit(data, line, "Error\nTexture path doubled");
	while (if_space(line[i]) && line[i])
		i++;
	while (if_upper(line[i]) && line[i])
		i++;
	while (if_space(line[i]) && line[i])
		i++;
	if (line[i] == '\0')
		info_read_exit(data, line, "Error\nTexture path not exist");
	data->info.tex_path[texture] = ft_strdup(&line[i]);
	if (ft_strchr_cub(data->info.tex_path[texture], ".xpm") != 1)
		info_read_exit(data, line, "Error\n.xpm not corrected");
	fd_tex = open(data->info.tex_path[texture], O_RDONLY);
	if (fd_tex < 0)
		info_read_exit(data, line, "Error\ntexture .xpm file doesn't exist");
	close(fd_tex);
	return (texture);
}

int	store_cub_data(t_data *data, char *line)
{
	int	i;

	i = 0;
	while (if_space(line[i]) == 1 && line[i])
		i++;
	if (line[i] == 'R' && line[i + 1] == ' ')
		return (check_resolution(data, line));
	else if (line[i] == 'N' && line[i + 1] == 'O')
		return (store_texture(TEX_NORTH, data, line));
	else if (line[i] == 'S' && line[i + 1] == 'O')
		return (store_texture(TEX_SOUTH, data, line));
	else if (line[i] == 'W' && line[i + 1] == 'E')
		return (store_texture(TEX_WEST, data, line));
	else if (line[i] == 'E' && line[i + 1] == 'A')
		return (store_texture(TEX_EAST, data, line));
	else if (line[i] == 'F' && line[i + 1] == ' ')
		return (store_color(FLOOR, data, line));
	else if (line[i] == 'C' && line[i + 1] == ' ')
		return (store_color(CEILING, data, line));
	else if (map_component_check(line))
		return (MAP);
	return (-1);
}

static void	store_loop(t_data *data)
{
	char	*line;

	while ((get_next_line(data->fd, &line)) > 0)
	{
		if ((line[0] == '\0' || line_empty_check(line) == 1)
			&& data->info.flag != MAP)
		{
			free(line);
			continue ;
		}
		data->info.flag = store_cub_data(data, line);
		if (data->info.flag == -1)
			info_read_exit(data, line, "Error\nParsing error");
		if (data->info.flag == MAP)
			break ;
		else
			free(line);
	}
	data->info.line = line;
}

void	find_data(t_data *data, char **file)
{
	data->fd = open(file[1], O_RDONLY);
	if (data->fd <= 0)
		error_msg("Error\nFile not found");
	store_loop(data);
}
