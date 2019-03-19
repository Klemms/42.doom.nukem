/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 10:47:38 by lde-batz          #+#    #+#             */
/*   Updated: 2018/11/12 11:32:48 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*src;
	unsigned char	car;

	src = (unsigned char*)s;
	car = (unsigned char)c;
	while (n--)
	{
		if (*src != car)
			src++;
		else
			return (src);
	}
	return (NULL);
}
