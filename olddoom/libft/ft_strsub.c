/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 19:01:36 by cababou           #+#    #+#             */
/*   Updated: 2018/08/30 06:07:30 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, size_t start, size_t len, size_t freeit)
{
	size_t	i;
	char	*nstring;

	if (s == NULL)
		return (NULL);
	i = 0;
	nstring = (char *)malloc(sizeof(char) * (len + 1));
	if (nstring == NULL)
		return (NULL);
	while (i < len)
	{
		nstring[i] = s[start + i];
		i++;
	}
	nstring[i] = '\0';
	if (freeit == 1)
		free((char *)s);
	return (nstring);
}
