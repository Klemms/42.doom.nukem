/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 18:48:06 by cababou           #+#    #+#             */
/*   Updated: 2019/03/12 11:03:46 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		if ((((unsigned char *)s)[i] == (unsigned char)c) || (c == '\0'
			&& ((unsigned char *)s) == '\0'))
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
