/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_read_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctchen <ctchen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:03:08 by ctchen            #+#    #+#             */
/*   Updated: 2023/08/28 12:03:17 by ctchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_find_color(t_data *data, char *line, char **rgb, char *temp)
{
	free(line);
	ft_free_2d(rgb);
	free(temp);
	free_tex_line(data);
	error_msg("Error\nRGB range invalid or info not corrected");
}

int	ft_strchr_cub(char *str, char *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ft_strcmp(str, cub) == 0 || cub[i] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		while (str[i + j] == cub[j])
		{
			if (cub[j + 1] == '\0' && str[i + j + 1] == '\0')
				return (1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
