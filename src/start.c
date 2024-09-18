/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwong <bwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:01:53 by bwong             #+#    #+#             */
/*   Updated: 2023/08/29 17:46:30 by ctchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//main + basic error handling

static int	file_extension(char *filename)
{
	int	i;

	i = ft_strlen(filename);
	if (i <= 4)
		return (1);
	else if (i > 4 && filename[i - 1] == 'b' && filename[i - 2] == 'u'
		&& filename[i - 3] == 'c' && filename[i - 4] == '.'
		&& filename[i - 5] == '/')
		return (1);
	else if (i > 4 && filename[i - 1] == 'b' && filename[i - 2] == 'u'
		&& filename[i - 3] == 'c' && filename[i - 4] == '.')
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2)
	{
		if (file_extension(argv[1]) == 1)
		{
			printf("Error\nGiven file is not .cub\n");
			return (1);
		}
		ft_init(&data, argv);
	}
	return (printf("Error\nWrong number of arguments\n"), 0);
}
