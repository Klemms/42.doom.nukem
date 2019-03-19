/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 10:16:24 by lde-batz          #+#    #+#             */
/*   Updated: 2018/11/12 15:16:51 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	cpy[len];

	if (len >= 134217728)
		return (NULL);
	ft_memcpy(cpy, src, len);
	ft_memcpy(dst, cpy, len);
	return (dst);
}
