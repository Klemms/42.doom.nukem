/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listcontainer_reindex.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 05:29:49 by cababou           #+#    #+#             */
/*   Updated: 2018/08/12 03:48:45 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	lstcontainer_reindex(t_lstcontainer *container)
{
	t_list	*element;
	int		i;

	element = container->firstelement;
	i = 0;
	while (element)
	{
		element->index = i;
		element = element->next;
		i++;
	}
}
