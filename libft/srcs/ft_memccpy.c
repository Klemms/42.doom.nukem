/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 11:35:08 by lde-batz          #+#    #+#             */
/*   Updated: 2018/11/14 11:23:08 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*rdst;
	const unsigned char	*rsrc;

	rdst = (unsigned char*)dst;
	rsrc = (const unsigned char*)src;
	while (n)
	{
		if ((*rdst++ = *rsrc++) == (unsigned char)c)
			return (rdst);
		n--;
	}
	return (NULL);
}
