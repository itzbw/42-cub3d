/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwong <bwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 21:28:38 by bwong             #+#    #+#             */
/*   Updated: 2023/08/21 09:41:32 by ctchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	set_player_dir(t_data *data, char c)
{
	if (c == 'N')
	{
		data->pl.dirx = -1;
		data->pl.planey = FOV;
	}
	else if (c == 'S')
	{
		data->pl.dirx = 1;
		data->pl.planey = -FOV;
	}
	else if (c == 'W')
	{
		data->pl.diry = -1;
		data->pl.planex = -FOV;
	}
	else if (c == 'E')
	{
		data->pl.diry = 1;
		data->pl.planex = FOV;
	}
}

void	player_init(t_data *data)
{
	data->pl.posx += ((double)MP_SCALE / 2) / 10;
	data->pl.posy += ((double)MP_SCALE / 2) / 10;
	set_player_dir(data, data->map.map[(int)data->pl.posy]
	[(int)data->pl.posx]);
	data->pl.front_back = 0;
	data->pl.left_right = 0;
	data->pl.walk_speed = 0.03;
	data->pl.look_speed = 0.03;
	data->map.map[(int)data->pl.posy][(int)data->pl.posx] = '0';
}
