/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 10:03:43 by lde-batz          #+#    #+#             */
/*   Updated: 2018/11/12 11:56:50 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	const char	*cpy;
	char		*res;
	char		temp[n];

	i = 0;
	cpy = (const char*)src;
	res = (char*)dst;
	while (i < n)
	{
		temp[i] = cpy[i];
		i++;
	}
	i = 0;
	while (i < n)
	{
		res[i] = temp[i];
		i++;
	}
	return (res);
}
