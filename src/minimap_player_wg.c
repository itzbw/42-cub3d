/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_lookline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctchen <ctchen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:45:56 by ctchen            #+#    #+#             */
/*   Updated: 2023/08/29 18:00:15 by ctchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	player_representation(t_data *data, double x, double y, int color)
{
	int	i;

	i = 0;
	if (x < CROSS_SIZE || (y + CROSS_SIZE) >= data->info.win_height
		|| (x + CROSS_SIZE) >= data->info.win_width || y < CROSS_SIZE)
	{
		printf("Error\nPlayer is out of map\n");
		return ;
	}
	while (i < CROSS_SIZE)
	{
		my_mlx_pixel_put(data, x, y + i, color);
		my_mlx_pixel_put(data, x, y - i, color);
		my_mlx_pixel_put(data, x + i, y, color);
		my_mlx_pixel_put(data, x - i, y, color);
		i++;
	}
}

void	minimap_wg_choose(t_data *data, int x, int y)
{
	if (data->map.map[y][x] == '1')
		minimap_draw_square(data, x, y, D_BLUE);
	else if (data->map.map[y][x] == '0')
		minimap_draw_square(data, x, y, WHITE);
}
