/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_alloc_and_free2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctchen <ctchen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:47:51 by ctchen            #+#    #+#             */
/*   Updated: 2023/08/29 14:57:02 by ctchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static char	*delete_space(char *str)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (int)ft_strlen(str) + 1);
	if (!new)
		free(new);
	while (str[i])
	{
		if (str[i] != ' ')
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}

void	rem_space_comma_check(t_data *data, char *line, int i, char **temp)
{
	int	x;
	int	count;

	x = 0;
	count = 0;
	while (line[x])
	{
		if ((x + 1) < (int)ft_strlen(line) && line[x] == ','
			&& line[x + 1] == ',')
			count++;
		x++;
	}
	if (count > 0)
		info_read_exit(data, line, "Error\nRGB format not recognized");
	(*temp) = delete_space(&line[i]);
}

void	info_read_exit(t_data *data, char *line, char *msg)
{
	free(line);
	free_tex_line(data);
	error_msg(msg);
}
