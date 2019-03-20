/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:36:53 by cababou           #+#    #+#             */
/*   Updated: 2017/12/13 18:58:01 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	size_t	i;
	void	*mem;

	if ((mem = malloc(size)))
	{
		i = 0;
		while ((sizeof(int) * i) < size)
		{
			((int *)mem)[i] = 0;
			i++;
		}
		return (mem);
	}
	return (NULL);
}
