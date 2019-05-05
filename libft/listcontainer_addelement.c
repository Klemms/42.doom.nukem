/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listcontainer_addelement.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 05:13:38 by cababou           #+#    #+#             */
/*   Updated: 2018/09/16 01:17:43 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	lstcontainer_add(t_lstcontainer *container, void *content)
{
	if (container == NULL)
		container = lstcontainer_new();
	if (container->firstelement == NULL)
	{
		container->firstelement = ft_lstnew(content);
		container->lastelement = container->firstelement;
	}
	else
		container->lastelement = ft_lstadd(container->lastelement,
			ft_lstnew(content));
}
