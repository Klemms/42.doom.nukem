/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listcontainer_removeelement.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 05:26:45 by cababou           #+#    #+#             */
/*   Updated: 2019/05/05 10:19:01 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	lstcontainer_remove(t_lstcontainer *l, t_list *element)
{
	if (element == l->firstelement && element == l->lastelement)
	{
		l->firstelement = NULL;
		l->lastelement = NULL;
	}
	if (element == l->firstelement && element->next == NULL)
		l->firstelement = NULL;
	if (element == l->lastelement && element->prev == NULL)
		l->lastelement = NULL;
	if (element == l->firstelement && element->next != NULL)
		l->firstelement = element->next;
	if (element == l->lastelement && element->prev != NULL)
		l->lastelement = element->prev;
	ft_lstdelone(element);
}
