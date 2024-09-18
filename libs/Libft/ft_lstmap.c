/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctchen <ctchen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:55:04 by ctchen            #+#    #+#             */
/*   Updated: 2021/12/10 15:04:05 by ctchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	t_list	*list2;

	if (!lst)
		return (0);
	list = ft_lstnew(f(lst->content));
	if (!list)
		return (0);
	list2 = list;
	while (lst)
	{
		if (lst->next)
		{
			list->next = ft_lstnew(f(lst->next->content));
			if (!list->next)
			{
				ft_lstclear(&list2, del);
				return (0);
			}
			list = list->next;
		}
		lst = lst->next;
	}
	list->next = 0;
	return (list2);
}
