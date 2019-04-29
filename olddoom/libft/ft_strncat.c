/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:54:16 by cababou           #+#    #+#             */
/*   Updated: 2017/12/03 17:10:06 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t startpos;
	size_t i;

	startpos = ft_strlen(s1);
	i = 0;
	while (i < n && s2[i] != '\0')
	{
		s1[startpos + i] = s2[i];
		i++;
	}
	s1[startpos + i] = '\0';
	return (s1);
}
