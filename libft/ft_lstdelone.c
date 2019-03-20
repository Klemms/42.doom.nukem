/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 20:09:47 by cababou           #+#    #+#             */
/*   Updated: 2018/08/30 06:07:14 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *el)
{
	t_list	*tmpelement;

	if (el)
	{
		if (el->prev)
			el->prev->next = el->next ? el->next : NULL;
		if (el->next)
		{
			el->next->prev = el->prev ? el->prev : NULL;
			tmpelement = el->next;
			while (tmpelement)
			{
				tmpelement->index--;
				tmpelement = tmpelement->next;
			}
		}
		if (el->content)
			free(el->content);
		free(el);
	}
}
