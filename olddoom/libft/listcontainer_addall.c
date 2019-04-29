/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listcontainer_addall.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 05:13:38 by cababou           #+#    #+#             */
/*   Updated: 2018/08/12 03:40:21 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	lstcontainer_addall(t_lstcontainer *dest, t_lstcontainer *cnt)
{
	t_list	*element;

	if (dest == NULL)
		dest = lstcontainer_new();
	element = cnt->firstelement;
	while (element)
	{
		if (dest->firstelement == NULL)
		{
			dest->firstelement = ft_lstnew(element->content);
			dest->lastelement = dest->firstelement;
		}
		else
		{
			dest->lastelement = ft_lstadd(dest->lastelement,
				ft_lstnew(element->content));
		}
		element = element->next;
	}
}
