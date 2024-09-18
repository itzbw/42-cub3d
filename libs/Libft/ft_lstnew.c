/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctchen <ctchen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 10:17:50 by ctchen            #+#    #+#             */
/*   Updated: 2021/12/10 10:17:50 by ctchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*strc;

	strc = (t_list *)malloc(sizeof(*strc));
	if (!strc)
		return (0);
	strc->content = content;
	strc->next = 0;
	return (strc);
}
