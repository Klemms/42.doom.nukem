/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mmalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 02:25:34 by cababou           #+#    #+#             */
/*   Updated: 2019/04/05 12:23:41 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*mmalloc(size_t size)
{
	void	*element;

	if (!(element = malloc(size)))
		return (NULL);
	ft_bzero(element, size);
	return (element);
}
