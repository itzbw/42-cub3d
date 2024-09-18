/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwong <bwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:30:18 by ctchen            #+#    #+#             */
/*   Updated: 2023/08/29 17:47:02 by ctchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_strlen_nl(char *str, int nb)
{
	int	i;
	int	count;
	int	nl;

	i = 0;
	count = 0;
	nl = -1;
	while (nl < nb && i < (int)ft_strlen(str))
	{
		if (str[i] == '\0' || str[i] == '\n')
			nl++;
		if (str[i] != '\n')
			count++;
		if (str[i] == '\n' && nl < nb)
			count = 0;
		i++;
	}
	return (count);
}

bool	str_check(char search, char *find)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(find))
	{
		if (search == find[i])
			return (1);
		i++;
	}
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x > data->info.win_width || y > data->info.win_height || x < 0 || y < 0)
		return ;
	dst = data->img.addr + (y * data->img.line_length + x
			* (data->img.bpp / 8));
		*(unsigned int *)dst = color;
}

int	error_msg(char *msg)
{
	printf("%s\n", msg);
	exit(1);
}
