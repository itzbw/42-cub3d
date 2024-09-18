/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwong <bwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 09:16:52 by ctchen            #+#    #+#             */
/*   Updated: 2023/08/29 17:45:58 by ctchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	calc(t_data *data)
{
	data->ray.hit = 0;
	data->ray.perpwalldist = 0;
	data->ray.camerax = 2 * data->ray.x / (double)data->info.win_width - 1;
	data->ray.raydirx = data->pl.dirx + data->pl.planex
		* data->ray.camerax;
	data->ray.raydiry = data->pl.diry + data->pl.planey
		* data->ray.camerax;
	data->ray.mapx = (int)data->pl.posx;
	data->ray.mapy = (int)data->pl.posy;
	if (data->ray.raydiry == 0)
		data->ray.deltadistx = 0;
	else if (data->ray.raydirx == 0)
		data->ray.deltadistx = 1;
	else
		data->ray.deltadistx = sqrt(1 + (data->ray.raydiry
					* data->ray.raydiry) / (data->ray.raydirx
					* data->ray.raydirx));
	if (data->ray.raydirx == 0)
		data->ray.deltadisty = 0;
	else if (data->ray.raydiry == 0)
		data->ray.deltadisty = 1;
	else
		data->ray.deltadisty = sqrt(1 + (data->ray.raydirx
					* data->ray.raydirx) / (data->ray.raydiry
					* data->ray.raydiry));
}

static void	checkcondition(t_data *data)
{
	if (data->ray.raydirx < 0)
	{
		data->ray.stepx = -1;
		data->ray.sidedistx = (data->pl.posy - data->ray.mapy)
			* data->ray.deltadistx;
	}
	else
	{
		data->ray.stepx = 1;
		data->ray.sidedistx = (data->ray.mapy + 1.0 - data->pl.posy)
			* data->ray.deltadistx;
	}
	if (data->ray.raydiry < 0)
	{
		data->ray.stepy = -1;
		data->ray.sidedisty = (data->pl.posx - data->ray.mapx)
			* data->ray.deltadisty;
	}
	else
	{
		data->ray.stepy = 1;
		data->ray.sidedisty = (data->ray.mapx + 1.0 - data->pl.posx)
			* data->ray.deltadisty;
	}
}

static void	ft_drawstartend(t_data *data)
{
	if (data->ray.wallside == TEX_NORTH || data->ray.wallside == TEX_SOUTH)
		data->ray.perpwalldist = ((double)data->ray.mapy
				- data->pl.posy + (1 - (double)data->ray.stepx) / 2)
			/ data->ray.raydirx;
	else if (data->ray.wallside == TEX_EAST || data->ray.wallside == TEX_WEST)
		data->ray.perpwalldist = ((double)data->ray.mapx
				- data->pl.posx + (1 - (double)data->ray.stepy) / 2)
			/ data->ray.raydiry;
	data->ray.lineheight = (int)(data->info.win_height
			/ data->ray.perpwalldist);
	data->ray.drawstart = -data->ray.lineheight / 2 + data->info.win_height / 2;
	if (data->ray.drawstart < 0 || data->ray.drawstart > data->info.win_height)
		data->ray.drawstart = 0;
	data->ray.drawend = data->ray.lineheight / 2 + data->info.win_height / 2;
	if (data->ray.drawend >= data->info.win_height || data->ray.drawend < 0)
		data->ray.drawend = data->info.win_height - 1;
	if (data->ray.wallside == TEX_NORTH || data->ray.wallside == TEX_SOUTH)
		data->ray.wall_x = data->pl.posx + data->ray.perpwalldist
			* data->ray.raydiry;
	else
		data->ray.wall_x = data->pl.posy + data->ray.perpwalldist
			* data->ray.raydirx;
	data->ray.wall_x -= floor(data->ray.wall_x);
	data->ray.tex_x = (int)(data->ray.wall_x * (double)TEX_WIDTH);
}

static void	walldistance(t_data *data)
{
	while (data->ray.hit == 0)
	{
		if (data->ray.sidedistx < data->ray.sidedisty)
		{
			data->ray.sidedistx += data->ray.deltadistx;
			data->ray.mapy += data->ray.stepx;
			data->ray.side = 0;
			if (data->ray.stepx > 0)
				data->ray.wallside = TEX_SOUTH;
			else if (data->ray.stepx < 0)
				data->ray.wallside = TEX_NORTH;
		}
		else
		{
			data->ray.sidedisty += data->ray.deltadisty;
			data->ray.mapx += data->ray.stepy;
			data->ray.side = 1;
			if (data->ray.stepy > 0)
				data->ray.wallside = TEX_EAST;
			else if (data->ray.stepy < 0)
				data->ray.wallside = TEX_WEST;
		}
		if (data->map.map[data->ray.mapy][data->ray.mapx] == '1')
				data->ray.hit = 1;
	}
}

void	raycasting(t_data *data)
{
	data->ray.x = 0;
	while (data->ray.x < data->info.win_width)
	{
		calc(data);
		checkcondition(data);
		walldistance(data);
		ft_drawstartend(data);
		wall_draw(data, data->ray.x);
		data->ray.x++;
	}
}
