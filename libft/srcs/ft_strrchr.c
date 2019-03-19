/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 11:52:58 by lde-batz          #+#    #+#             */
/*   Updated: 2018/11/12 17:13:23 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*res;

	res = NULL;
	if (c == 0)
		return ((char*)s + ft_strlen(s));
	while (*s)
	{
		if (*s == c)
			res = (char*)s;
		s++;
	}
	return (res);
}
