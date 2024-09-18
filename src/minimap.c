/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctchen <ctchen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:01:50 by ctchen            #+#    #+#             */
/*   Updated: 2023/08/29 17:48:15 by ctchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	minimap_draw_square(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < MP_SCALE - 1)
	{
		my_mlx_pixel_put(data, ((x - data->pl.posx) * MP_SCALE)
			+ i + 1 + 70, ((y - data->pl.posy) * MP_SCALE)
			+ data->info.win_height - 70, color);
		my_mlx_pixel_put(data, ((x - data->pl.posx) * MP_SCALE) + 1 + 70,
			((y - data->pl.posy) * MP_SCALE)
			+ i + data->info.win_height - 70, color);
		i++;
	}
	while (j++ < MP_SCALE - 1)
	{
		my_mlx_pixel_put(data, ((x - data->pl.posx) * MP_SCALE)
			+ i + 1 + 70, ((y - data->pl.posy) * MP_SCALE)
			+ j + data->info.win_height - 70, color);
		my_mlx_pixel_put(data, ((x - data->pl.posx) * MP_SCALE)
			+ j + 1 + 70, ((y - data->pl.posy) * MP_SCALE)
			+ i + data->info.win_height - 70, color);
	}
}

static void	minimap_draw(t_data *data, int *xymax)
{
	int	temp;

	temp = xymax[2];
	while (xymax[0] < xymax[1])
	{
		while (xymax[2] < xymax[3])
		{
			minimap_wg_choose(data, data->pl.posx + xymax[2],
				data->pl.posy + xymax[0]);
			xymax[2]++;
		}
		xymax[0]++;
		xymax[2] = temp;
	}
	player_representation(data, 70, data->info.win_height - 71, GREEN);
}

static void	minimap_calc_hori(t_data *data, int limit, int *xymax)
{
	int	i;

	i = limit * -1 + 1;
	while ((int)data->pl.posx + i < data->map.width_count && i < limit)
	{
		while ((int)data->pl.posx + i < 0)
			i++;
		if (xymax[2] == 0)
			xymax[2] = i;
		i++;
	}
	xymax[3] = i;
	minimap_draw(data, xymax);
}

static void	minimap_representation(t_data *data, int *xymax)
{
	int	i;
	int	limit;

	limit = 5;
	i = limit * -1 + 1;
	while ((int)data->pl.posy + i < data->map.height_count && i < limit)
	{
		while ((int)data->pl.posy + i < 0)
			i++;
		if (xymax[0] == 0)
			xymax[0] = i;
		i++;
	}
	xymax[1] = i;
	minimap_calc_hori(data, limit, xymax);
}

void	minimap(t_data *data)
{
	int	*xymax;
	int	x;

	x = 0;
	xymax = malloc(sizeof(int) * 5 + 1);
	while (x < 5)
	{
		xymax[x] = 0;
		x++;
	}
	minimap_representation(data, xymax);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
		data->img.img_ptr, 0, 0);
	free(xymax);
}
