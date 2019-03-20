/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 04:29:03 by cababou           #+#    #+#             */
/*   Updated: 2018/09/04 03:55:27 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstget(size_t index, t_list *anyelement)
{
	t_list	*el;

	if (anyelement == NULL)
		return (NULL);
	el = ft_lstgetfirst(anyelement);
	while (el != NULL)
	{
		if (el->index == index)
			return (el);
		el = el->next;
	}
	return (NULL);
}
