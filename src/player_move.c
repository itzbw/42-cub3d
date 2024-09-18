/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctchen <ctchen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 11:32:23 by ctchen            #+#    #+#             */
/*   Updated: 2023/08/18 17:28:00 by ctchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	player_view_rotate_left(t_data *data, double oldplanex,
			double olddirx)
{
	if (data->pl.look_dir == -1)
	{
		olddirx = data->pl.dirx;
		oldplanex = data->pl.planex;
		data->pl.dirx = data->pl.dirx * cos(data->pl.look_speed / 2)
			- data->pl.diry * sin(data->pl.look_speed / 2);
		data->pl.diry = olddirx * sin(data->pl.look_speed / 2)
			+ data->pl.diry * cos(data->pl.look_speed / 2);
		data->pl.planex = data->pl.planex * cos(data->pl.look_speed / 2)
			- data->pl.planey * sin(data->pl.look_speed / 2);
		data->pl.planey = oldplanex * sin(data->pl.look_speed / 2)
			+ data->pl.planey * cos(data->pl.look_speed / 2);
	}
}

static void	player_view_rotate(t_data *data)
{
	double	oldplanex;
	double	olddirx;

	oldplanex = data->pl.planex;
	olddirx = data->pl.dirx;
	if (data->pl.look_dir == 1)
	{
		data->pl.dirx = data->pl.dirx * cos(-data->pl.look_speed / 2)
			- data->pl.diry * sin(-data->pl.look_speed / 2);
		data->pl.diry = olddirx * sin(-data->pl.look_speed / 2)
			+ data->pl.diry * cos(-data->pl.look_speed / 2);
		data->pl.planex = data->pl.planex * cos(-data->pl.look_speed / 2)
			- data->pl.planey * sin(-data->pl.look_speed / 2);
		data->pl.planey = oldplanex * sin(-data->pl.look_speed / 2)
			+ data->pl.planey * cos(-data->pl.look_speed / 2);
	}
	player_view_rotate_left(data, oldplanex, olddirx);
}

static void	player_strafing(t_data *data)
{
	if (data->pl.left_right == 1)
	{
		if (data->map.map[(int)(data->pl.posy + data->pl.diry
				* (data->pl.walk_speed))]
			[(int)data->pl.posx] == '0')
			data->pl.posy += data->pl.diry * data->pl.walk_speed;
		if (data->map.map[(int)data->pl.posy]
			[(int)(data->pl.posx - data->pl.dirx
				* (data->pl.walk_speed))] == '0')
			data->pl.posx -= data->pl.dirx * data->pl.walk_speed;
	}
	if (data->pl.left_right == -1)
	{
		if (data->map.map[(int)(data->pl.posy - data->pl.diry
				* (data->pl.walk_speed))]
			[(int)data->pl.posx] == '0')
			data->pl.posy -= data->pl.diry * data->pl.walk_speed;
		if (data->map.map[(int)data->pl.posy]
			[(int)(data->pl.posx + data->pl.dirx
				* (data->pl.walk_speed))] == '0')
			data->pl.posx += data->pl.dirx * data->pl.walk_speed;
	}
	player_view_rotate(data);
}

void	player_move(t_data *data)
{
	if (data->pl.front_back == 1)
	{
		if (data->map.map[(int)(data->pl.posy
				+ data->pl.dirx * data->pl.walk_speed)]
			[(int)data->pl.posx] == '0')
			data->pl.posy += data->pl.dirx * data->pl.walk_speed;
		if (data->map.map[(int)(data->pl.posy)][(int)(data->pl.posx
				+ (data->pl.diry * data->pl.walk_speed))] == '0')
			data->pl.posx += data->pl.diry * data->pl.walk_speed;
	}
	else if (data->pl.front_back == -1)
	{
		if (data->map.map[(int)(data->pl.posy
				- (data->pl.dirx * data->pl.walk_speed))]
			[(int)(data->pl.posx)] == '0')
			data->pl.posy -= data->pl.dirx * data->pl.walk_speed;
		if (data->map.map[(int)(data->pl.posy)][(int)(data->pl.posx
				- (data->pl.diry * data->pl.walk_speed))] == '0')
			data->pl.posx -= data->pl.diry * data->pl.walk_speed;
	}
	player_strafing(data);
}
