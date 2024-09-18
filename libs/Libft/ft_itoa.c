/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctchen <ctchen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:45:16 by ctchen            #+#    #+#             */
/*   Updated: 2021/12/04 11:26:39 by ctchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countnumb(int n)
{
	int	size;

	size = 0;
	if (n == 0)
		return (1);
	else if (n <= -2147483648)
		return (11);
	else if (n < 0)
	{
		size++;
		n = n * -1;
	}
	while (n > 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

static char	*ft_itcalc(char *str, int temp, int max)
{
	if (temp == -2147483648)
	{
		temp = temp / 10;
		temp = temp * -1;
		str[0] = '-';
		str[max] = '8';
		max--;
	}
	while (temp > 0)
	{
		str[max] = temp % 10 + '0';
		temp = temp / 10;
		max--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		max;
	int		temp;

	temp = n;
	max = ft_countnumb(n) - 1;
	str = malloc(sizeof(char) * ft_countnumb(n) + 1);
	if (!str)
		return (0);
	if (temp == 0)
		str[0] = 0 + '0';
	else if (temp < 0 && temp != -2147483648)
	{
		str[0] = '-';
		temp = temp * -1;
	}
	ft_itcalc(str, temp, max);
	str[ft_countnumb(n)] = '\0';
	return (str);
}
