/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:58:38 by cababou           #+#    #+#             */
/*   Updated: 2017/12/02 20:04:41 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t startpos;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (dst[i] != '\0' && i < size)
		i++;
	startpos = i;
	while (src[i - startpos] && i < size - 1)
	{
		dst[i] = src[i - startpos];
		i++;
	}
	if (startpos < size)
		dst[i] = '\0';
	return (ft_strlen(src) + startpos);
}
