/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctchen <ctchen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 10:50:04 by ctchen            #+#    #+#             */
/*   Updated: 2021/12/10 15:03:09 by ctchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;
	t_list	*next;

	curr = *lst;
	if (lst && *lst)
	{
		while (curr)
		{
			next = curr->next;
			del(curr->content);
			free(curr);
			curr = next;
		}
		*lst = NULL;
	}
}
