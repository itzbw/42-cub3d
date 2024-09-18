/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctchen <ctchen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:10:27 by ctchen            #+#    #+#             */
/*   Updated: 2021/12/06 15:35:28 by ctchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_rota(char const *s1, char const *set, int i)
{
	int	j;

	j = 0;
	while (set[j])
	{
		if (s1[i] == set[j])
			return (1);
		j++;
	}
	return (0);
}

static char	*ft_substr2(char const *s, unsigned int start, unsigned int end)
{
	char			*ptr;
	unsigned int	i;

	i = 0;
	ptr = malloc(sizeof(char) * (end + 1) - start + 1);
	if (!ptr)
		return (0);
	while (start <= end)
	{
		ptr[i] = s[start];
		i++;
		start++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	end;

	i = 0;
	if (!s1 || !set)
		return (0);
	else if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	end = ft_strlen(s1) - 1;
	while (ft_rota(s1, set, i) == 1 && s1[i])
		i++;
	while (ft_rota(s1, set, end) == 1 && s1[i])
		end--;
	return (ft_substr2(s1, i, end));
}
