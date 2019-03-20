/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 19:54:20 by cababou           #+#    #+#             */
/*   Updated: 2017/12/13 18:58:27 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;
	void	*returndst;

	returndst = (void *)malloc(sizeof(unsigned char) * n);
	i = 0;
	returndst = dst;
	while (i < n)
	{
		((unsigned char *)returndst)[i] = ((unsigned char *)dst)[i];
		i++;
	}
	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		if (((unsigned char *)src)[i] == ((unsigned char)c))
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
