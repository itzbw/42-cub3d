/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_release.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwong <bwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:07:24 by bwong             #+#    #+#             */
/*   Updated: 2023/08/28 16:20:10 by ctchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	key_movement(int keycode, t_data *data)
{
	if (keycode == W_FRONT)
		data->pl.front_back = +1;
	if (keycode == S_BACK)
		data->pl.front_back = -1;
	if (keycode == A_LEFT)
		data->pl.left_right = +1;
	if (keycode == D_RIGHT)
		data->pl.left_right = -1;
}

int	press_key(int keycode, t_data *data)
{
	if (keycode == ESC)
	{
		close_window(data);
		exit (0);
	}
	key_movement(keycode, data);
	if (keycode == LOOK_RIGHT)
		data->pl.look_dir = 1;
	if (keycode == LOOK_LEFT)
		data->pl.look_dir = -1;
	return (0);
}

int	release_key(int keycode, t_data *game)
{
	if (keycode == W_FRONT)
		game->pl.front_back = 0;
	if (keycode == S_BACK)
		game->pl.front_back = 0;
	if (keycode == A_LEFT)
		game->pl.left_right = 0;
	if (keycode == D_RIGHT)
		game->pl.left_right = 0;
	if (keycode == LOOK_RIGHT)
		game->pl.look_dir = 0;
	if (keycode == LOOK_LEFT)
		game->pl.look_dir = 0;
	return (0);
}

int	exit_key(t_data *data)
{
	close_window (data);
	error_msg ("EXIT: WINDOW CLOSED");
	exit (0);
}
