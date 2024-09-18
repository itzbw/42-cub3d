/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctchen <ctchen@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:57:34 by ctchen            #+#    #+#             */
/*   Updated: 2021/12/01 13:42:54 by ctchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s1)
{
	int		i;
	int		size_src;
	char	*tab;

	i = 0;
	size_src = 0;
	while (s1[size_src])
		size_src++;
	tab = malloc(sizeof(*tab) * size_src + 1);
	if (!tab)
		return (0);
	while (i < size_src)
	{
		tab[i] = s1[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
