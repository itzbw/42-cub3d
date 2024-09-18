/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwong <bwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:27:17 by ctchen            #+#    #+#             */
/*   Updated: 2023/08/29 17:51:24 by ctchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <X11/X.h>
# include <stdbool.h>
# include <math.h>
# include "../libs/Libft/libft.h"
# include "../libs/mlx_linux/mlx.h"

# define BUFFER_SIZE 6000
# define FOV 0.66

# define MP_SCALE 11
# define CROSS_SIZE 4

# define TEXTURE_WALL "Texture/EA_TECH_4A.ppm"

// Key codes
# define ESC 65307
# define W_FRONT 119
# define S_BACK 115
# define A_LEFT 100
# define D_RIGHT 97
# define LOOK_LEFT 65361
# define LOOK_RIGHT 65363

//colors hexcode
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define TEAL 0x00008080
# define MAGENTA 0x00FF00FF
# define BLACK 0x00000000
# define WHITE 0x00FFFFFF
# define D_BLUE 0x000763D3

//TEXTURE
# define TEX_HEIGHT 64
# define TEX_WIDTH 64
# define TEXTURE 4
# define TEX_NORTH 0
# define TEX_SOUTH 1
# define TEX_WEST 2
# define TEX_EAST 3
# define RESOLUTION 6
# define FLOOR 7
# define CEILING 8
# define MAP 9

# define PLAYER_CHAR "NSWE"
# define TITLE_SIZE 64 // or 72, we can chnage later

typedef struct s_winfo
{
	char	*line;
	int		flag;
	int		win_width;
	int		win_height;
	int		floor_color;
	int		ceiling_color;
	char	*tex_path[TEXTURE];
	int		texture[TEXTURE][TEX_HEIGHT * TEX_WIDTH];
}			t_winfo;

typedef struct s_map
{
	char	*tmp;
	char	**buff;
	char	**map;
	int		width_count;
	int		height_count;
}			t_map;

// Player infos (Needed for First person view)
typedef struct s_pl
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	int			pcount;
	int			front_back;
	int			left_right;
	double		look_dir;
	double		walk_speed;
	double		look_speed;
}	t_pl;

typedef struct s_ray
{
	double		raydirx;
	double		raydiry;
	double		camerax;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	double		perpwalldist;
	int			mapx;
	int			mapy;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			x;
	int			wallside;
	double		step;
	double		tex_pos;
	double		wall_x;
	int			tex_x;
	int			tex_y;
}				t_ray;

typedef struct s_img
{
	int		bpp;
	int		*data;
	int		size_l;
	int		width;
	int		height;
	int		line_length;
	int		endian;
	void	*img_ptr;
	char	*addr;
}				t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*mlx_win;
	int		fd;
	int		**buf;
	t_img	img;
	t_pl	pl;
	t_ray	ray;
	t_map	map;
	t_winfo	info;
}				t_data;

//init.c
void	ft_init(t_data *data, char **argv);

//gnl
int		get_next_line(int fd, char **line);

//raycasting.c
void	raycasting(t_data *data);

//raycasting_draw.c
void	load_texture(t_data *data);
void	render_screen(t_data *data);
void	wall_draw(t_data *data, int x);

//minimap.c
void	minimap_draw_square(t_data *data, int i, int j, int color);
void	minimap(t_data *data);

//minimap_player_wg.c
void	player_representation(t_data *data, double x, double y, int color);
void	minimap_wg_choose(t_data *data, int x, int y);

//player_move.c
void	player_move(t_data *data);

//player_init.c
void	player_init(t_data *data);

//game_loop.c
void	mlx_start(t_data *data);

// key_press_release
int		press_key(int keycode, t_data *game);
int		release_key(int keycode, t_data *game);
int		exit_key(t_data *data);

//exit_window
void	close_window(t_data *data);

//info_read.c
void	find_data(t_data *data, char **file);

//info_check.c
void	read_map(t_data *data, char *line);

//check_map.c
int		line_empty_check(char *line);
void	data_check(t_data *data);
int		map_component_check(char *line);
int		valid_map(char **map, int ylimit);

//info_read2.c
int		check_resolution(t_data *data, char *line);
int		store_cub_data(t_data *data, char *line);
int		store_color(int info, t_data *data, char *line);

//================================================utils files
//utils.c
int		ft_strlen_nl(char *str, int nb);
int		error_msg(char *msg);
bool	str_check(char search, char *find);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

//utils2.c
int		if_digit(char *str);
int		if_space(int i);
int		if_upper(char c);
int		ft_strcmp(char *s1, char *s2);

//utils_alloc_and_free2.c
void	info_read_exit(t_data *data, char *line, char *msg);
void	rem_space_comma_check(t_data *data, char *line, int i, char **temp);

//utils_alloc_and_free.c
void	allocate_map_buffer(t_data *data);
void	ft_free_data_buf(int **buf);
void	ft_free_2d(char **map);
void	free_tex_line(t_data *data);
void	free_fill_map(t_data *data);

//info_read_utils.c
void	free_find_color(t_data *data, char *line, char **rgb, char *temp);
int		ft_strchr_cub(char *str, char *cub);

#endif
