/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctchen <ctchen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:45:06 by ctchen            #+#    #+#             */
/*   Updated: 2021/12/10 16:47:12 by ctchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_freeloc(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}

static int	ft_countwords(char const *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
		{
			word++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (word);
}

static int	ft_wordlength(char const *scopy, char c, int j)
{
	int	i;
	int	nb;
	int	x;

	i = 0;
	nb = 0;
	x = 0;
	while (x < j + 1)
	{
		while (scopy[i] && scopy[i] == c)
			i++;
		x++;
		if (x != j + 1)
			while (scopy[i] && scopy[i] != c)
				i++;
	}
	while (scopy[i] && scopy[i] != c)
	{
		i++;
		nb++;
	}
	return (nb);
}

static char	*ft_strcopy(char *dest, char c, char const *scopy, int j)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (x < j + 1 && scopy[i])
	{
		while (scopy[i] == c && scopy[i])
			i++;
		x++;
		if (x != j + 1)
			while (scopy[i] != c && scopy[i])
				i++;
	}
	x = 0;
	while (scopy[i] != c && scopy[i])
	{
		dest[x] = scopy[i];
		x++;
		i++;
	}
	dest[x] = '\0';
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		nb_words;
	int		j;

	j = 0;
	if (!s)
		return (0);
	nb_words = ft_countwords(s, c);
	str = malloc(sizeof(char *) * (nb_words + 1));
	if (!str)
		ft_freeloc(str);
	while (j < nb_words)
	{
		str[j] = malloc(sizeof(char) * ft_wordlength(s, c, j) + 1);
		if (!str[j])
			ft_freeloc(str);
		ft_strcopy(str[j], c, s, j);
		j++;
	}
	str[j] = NULL;
	return (str);
}
