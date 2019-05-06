/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 19:01:36 by cababou           #+#    #+#             */
/*   Updated: 2019/05/06 02:30:49 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char *s, size_t start, size_t len, size_t freeit)
{
	size_t	i;
	char	*nstring;

	if (s == NULL)
		return (NULL);
	i = 0;
	if (!(nstring = ft_strnew(len, 0)))
		return (NULL);
	while (i < len)
	{
		nstring[i] = s[start + i];
		i++;
	}
	nstring[i] = '\0';
	if (freeit == 1)
	{
		free(s);
		s = NULL;
	}
	return (nstring);
}
