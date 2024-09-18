/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctchen <ctchen@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:17:42 by ctchen            #+#    #+#             */
/*   Updated: 2021/12/03 12:48:47 by ctchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t			i;
	unsigned int	dst_size;
	unsigned int	src_size;

	i = 0;
	dst_size = ft_strlen(dst);
	src_size = ft_strlen((char *)src);
	if (dstsize == 0)
		return (src_size);
	if (dstsize <= dst_size)
		return (dstsize + src_size);
	while (src[i] && i < dstsize - dst_size - 1)
	{
		dst[dst_size + i] = src[i];
		i++;
	}
	dst[dst_size + i] = '\0';
	return (dst_size + src_size);
}
