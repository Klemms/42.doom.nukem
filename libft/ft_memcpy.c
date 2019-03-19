/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 16:03:57 by cababou           #+#    #+#             */
/*   Updated: 2017/12/13 18:59:19 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	void	*returndst;

	returndst = (void *)malloc(sizeof(char) * n);
	i = 0;
	returndst = dst;
	while (i < n)
	{
		((char *)returndst)[i] = ((char *)dst)[i];
		i++;
	}
	i = 0;
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (returndst);
}
