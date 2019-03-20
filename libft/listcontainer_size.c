/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listcontainer_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 05:29:49 by cababou           #+#    #+#             */
/*   Updated: 2018/02/17 05:36:54 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		lstcontainer_size(t_lstcontainer *list_container)
{
	t_list	*lst;
	int		size;

	size = 0;
	lst = list_container->firstelement;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}
