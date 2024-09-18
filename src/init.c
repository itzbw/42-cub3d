/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwong <bwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:55:09 by ctchen            #+#    #+#             */
/*   Updated: 2023/08/28 12:44:28 by ctchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_map(t_map *map)
{
	map->tmp = NULL;
	map->buff = NULL;
	map->map = NULL;
	map->width_count = 0;
	map->height_count = 0;
}

static void	info_init(t_winfo *info)
{
	int	i;

	i = 0;
	info->line = NULL;
	info->flag = 0;
	info->win_width = 0;
	info->win_height = 0;
	info->floor_color = -1;
	info->ceiling_color = -1;
	while (i < TEXTURE)
	{
		info->tex_path[i] = NULL;
		i++;
	}
}

static void	ray_init(t_ray *ray)
{
	ray->raydirx = 0;
	ray->raydiry = 0;
	ray->camerax = 0;
	ray->sidedistx = 0;
	ray->sidedisty = 0;
	ray->deltadistx = 0;
	ray->deltadisty = 0;
	ray->perpwalldist = 0;
	ray->mapx = 0;
	ray->mapy = 0;
	ray->stepx = 0;
	ray->stepy = 0;
	ray->hit = 0;
	ray->side = 0;
	ray->lineheight = 0;
	ray->drawstart = 0;
	ray->drawend = 0;
	ray->x = 0;
	ray->wallside = 0;
	ray->step = 0;
	ray->wall_x = 0;
}

static void	data_init(t_data *data)
{
	data->pl.pcount = 0;
	data->pl.posx = 0;
	data->pl.posy = 0;
	data->pl.dirx = 0;
	data->pl.diry = 0;
	data->pl.planex = 0;
	data->pl.planey = 0;
	data->pl.front_back = 0;
	data->pl.left_right = 0;
	data->pl.look_dir = 0;
	data->pl.walk_speed = 0;
	data->pl.look_speed = 0;
	data->img.height = 0;
	data->img.width = 0;
	ray_init(&data->ray);
	info_init(&data->info);
	init_map(&data->map);
}

void	ft_init(t_data *data, char **argv)
{
	data_init(data);
	find_data(data, argv);
	data_check(data);
	read_map(data, data->info.line);
	if (valid_map(data->map.map, data->map.height_count) == 1)
	{
		ft_free_2d(data->map.map);
		free_tex_line(data);
		exit (1);
	}
	player_init(data);
	mlx_start(data);
}
