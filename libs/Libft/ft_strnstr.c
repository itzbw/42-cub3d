/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctchen <ctchen@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:39:23 by ctchen            #+#    #+#             */
/*   Updated: 2021/12/06 14:22:20 by ctchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (ft_strlen((char *)needle) == 0)
		return ((char *)haystack);
	else if (ft_strlen((char *)haystack) == 0)
		return (0);
	while (i < len)
	{
		if (ft_strncmp((char *)&haystack[i], needle, ft_strlen((char *)needle))
			== 0)
		{
			if (ft_strlen((char *)needle) + i > len)
				return (0);
			return ((char *)&haystack[i]);
		}
		i++;
	}
	return (0);
}
