/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 16:49:24 by cababou           #+#    #+#             */
/*   Updated: 2017/12/13 19:45:03 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int i2;

	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != '\0')
	{
		i2 = 0;
		while (needle[i2] == haystack[i])
		{
			i++;
			i2++;
			if (needle[i2] == '\0')
				return (((char *)haystack) + i - ft_strlen(needle));
		}
		i = i - i2;
		i++;
	}
	return (NULL);
}
