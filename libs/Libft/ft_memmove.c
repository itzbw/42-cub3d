/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctchen <cychen@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:45:54 by ctchen            #+#    #+#             */
/*   Updated: 2021/12/06 11:55:32 by ctchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*serc;
	size_t	i;

	serc = (char *)src;
	i = 0;
	if (dst == src)
		return (dst);
	if ((char *)dst > serc)
	{
		while (len > 0)
		{
			len--;
			((char *)dst)[len] = serc[len];
		}
	}
	else
	{
		while (i < len)
		{
			((char *)dst)[i] = serc[i];
			i++;
		}
	}
	return (dst);
}
