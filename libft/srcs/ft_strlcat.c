/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:43:59 by lde-batz          #+#    #+#             */
/*   Updated: 2018/11/14 11:39:15 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		dlen;
	size_t		slen;
	const char	*s;
	char		*d;

	i = 0;
	s = src;
	d = dst;
	dlen = ft_strlen(d);
	slen = ft_strlen(s);
	if (size < dlen)
		return (size + slen);
	while (dlen + i < size - 1 && i < slen)
	{
		d[dlen + i] = s[i];
		i++;
	}
	d[dlen + i] = '\0';
	return (dlen + slen);
}
