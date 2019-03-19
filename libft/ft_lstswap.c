/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 02:40:21 by cababou           #+#    #+#             */
/*   Updated: 2018/02/17 04:22:33 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	swapnextprev(t_list *el1, t_list *el2)
{
	t_list	*el2prev;
	t_list	*el2next;

	el2prev = el2->prev;
	el2next = el2->next;
	if (el1->prev)
		el1->prev->next = el2;
	el2->prev = el1->prev;
	if (el1->next)
		el1->next->prev = (el1->next == el2) ? el1->prev : el2;
	el2->next = (el1->next == el2) ? el1 : el1->next;
	if (el2prev && el1->next != el2)
		el2prev->next = el1;
	el1->prev = (el2prev == el1) ? el2 : el2prev;
	if (el2next)
		el2next->prev = el1;
	el1->next = el2next;
}

void	ft_lstswap(t_list *anyelement, int index1, int index2)
{
	t_list	*el1;
	t_list	*el2;

	el1 = ft_lstget(index1, anyelement);
	el2 = ft_lstget(index2, anyelement);
	swapnextprev(el1, el2);
	el1->index = index2;
	el2->index = index1;
}
