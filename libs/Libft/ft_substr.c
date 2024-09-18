/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctchen <ctchen@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 11:18:37 by ctchen            #+#    #+#             */
/*   Updated: 2021/12/10 10:15:25 by ctchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ptr;
	unsigned int	i;

	i = 0;
	if (!s)
		return (0);
	else if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		ptr = malloc(sizeof(char) * ft_strlen(s) + 1);
	else
		ptr = malloc(sizeof(char) * len + 1);
	if (!ptr)
		return (0);
	while (s[i] && i < len)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
