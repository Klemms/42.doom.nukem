/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listcontainer_fastsize.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 05:29:49 by cababou           #+#    #+#             */
/*   Updated: 2018/09/01 05:16:04 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		lstcontainer_fastsize(t_lstcontainer *container)
{
	if (container->lastelement == NULL)
		return (0);
	return (container->lastelement->index + 1);
}
