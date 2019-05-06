/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:00:13 by cababou           #+#    #+#             */
/*   Updated: 2019/03/13 13:58:26 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t i2;
	size_t possibleoccurence;

	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	i = 0;
	possibleoccurence = 0;
	while (haystack[i] != '\0' && i < len)
	{
		i2 = 0;
		possibleoccurence = i;
		while ((i + i2) < len && haystack[i] != '\0'
			&& needle[i2] == haystack[i + i2])
		{
			if (needle[i2 + 1] == '\0')
				return ((char *)(haystack + possibleoccurence));
			i2++;
		}
		i++;
	}
	return (NULL);
}
