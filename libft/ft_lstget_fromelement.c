/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget_fromelement.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 04:29:03 by cababou           #+#    #+#             */
/*   Updated: 2018/08/14 05:24:16 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstget_fromelement(size_t index, t_list *element)
{
	t_list	*el;

	el = element;
	while (el != NULL)
	{
		if (el->index == index)
			return (el);
		el = el->next;
	}
	return (NULL);
}
