/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwong <bwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:24:02 by ctchen            #+#    #+#             */
/*   Updated: 2023/08/29 18:09:21 by ctchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	load_img(t_data *data, int *texture, char *path, t_img *img)
{
	int	x;
	int	y;

	img->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, path, &img->width,
			&img->height);
	img->data = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_l,
			&img->endian);
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			texture[img->width * y + x] = img->data[img->width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(data->mlx_ptr, img->img_ptr);
}

void	load_texture(t_data *data)
{
	t_img	img;

	load_img(data, data->info.texture[TEX_NORTH],
		data->info.tex_path[TEX_NORTH], &img);
	free(data->info.tex_path[TEX_NORTH]);
	load_img(data, data->info.texture[TEX_EAST], data->info.tex_path[TEX_EAST],
		&img);
	free(data->info.tex_path[TEX_EAST]);
	load_img(data, data->info.texture[TEX_WEST], data->info.tex_path[TEX_WEST],
		&img);
	free(data->info.tex_path[TEX_WEST]);
	load_img(data, data->info.texture[TEX_SOUTH],
		data->info.tex_path[TEX_SOUTH], &img);
	free(data->info.tex_path[TEX_SOUTH]);
}

void	render_screen(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->info.win_height)
	{
		x = 0;
		while (x < data->info.win_width)
		{
			data->img.data[data->info.win_width * y + x] = data->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
		data->img.img_ptr, 0, 0);
}

static void	raycasting_draw(t_data *data)
{
	int	col;

	col = 0;
	while (col < data->ray.drawstart)
	{
		data->buf[col][data->ray.x] = data->info.ceiling_color;
		col++;
	}
	col = data->ray.drawend;
	while (col < data->info.win_height)
	{
		data->buf[col][data->ray.x] = data->info.floor_color;
		col++;
	}
}

void	wall_draw(t_data *data, int x)
{
	int	y;
	int	color;

	raycasting_draw(data);
	y = data->ray.drawstart;
	data->ray.step = 1.0 * TEX_HEIGHT / data->ray.lineheight;
	data->ray.tex_pos = (data->ray.drawstart - data->info.win_height / 2
			+ data->ray.lineheight / 2) * data->ray.step;
	while (y < data->ray.drawend)
	{
		data->ray.tex_y = (int)data->ray.tex_pos & (TEX_HEIGHT - 1);
		data->ray.tex_pos += data->ray.step;
		color = data->info.texture[data->ray.wallside]
		[TEX_HEIGHT * data->ray.tex_y + data->ray.tex_x];
		data->buf[y][x] = color;
		y++;
	}
}
