/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwong <bwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 10:41:23 by ctchen            #+#    #+#             */
/*   Updated: 2023/08/29 17:57:04 by ctchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	game_loop(t_data *data)
{
	if ((int)data->pl.posx == 0 || (int)data->pl.posy == 0
		|| data->pl.pcount != 1)
	{
		if (data->pl.pcount != 1)
			printf("Error\nPlayer count invalid\n");
		else
			printf("Error\nPlayer position is not valid\n");
		close_window(data);
		exit (1);
	}
	raycasting(data);
	player_move(data);
	render_screen(data);
	minimap(data);
	return (0);
}

static void	prepare_map_tex(t_data *data)
{
	allocate_map_buffer(data);
	load_texture(data);
}

void	mlx_start(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	{
		printf("Error\nmlx init failed\n");
		return ;
	}
	prepare_map_tex(data);
	data->mlx_win = mlx_new_window(data->mlx_ptr, data->info.win_width,
			data->info.win_height, "full snack");
	if (!data->mlx_win)
	{
		printf("Error\nwin loading failed\n");
		return ;
	}
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, data->info.win_width,
			data->info.win_height);
	data->img.addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bpp,
			&data->img.line_length, &data->img.endian);
	data->img.data = (int *)mlx_get_data_addr(data->img.img_ptr,
			&data->img.bpp, &data->img.size_l, &data->img.endian);
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, press_key, data);
	mlx_hook(data->mlx_win, KeyRelease, KeyReleaseMask, release_key, data);
	mlx_hook(data->mlx_win, DestroyNotify, ButtonPressMask, &exit_key, data);
	mlx_loop_hook(data->mlx_ptr, game_loop, data);
	mlx_loop(data->mlx_ptr);
}
