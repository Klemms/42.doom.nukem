/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 19:13:16 by cababou           #+#    #+#             */
/*   Updated: 2019/05/05 09:37:34 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_it2(char const **s1, size_t free_level)
{
	if (free_level == 1)
		ffree((char *)(*s1));
}

char	*ft_charjoin(char const *s1, char c2, size_t free_level)
{
	size_t	i;
	char	*nstring;
	size_t	size_s1;

	size_s1 = ft_strlen(s1);
	if (s1 == NULL)
		return (NULL);
	if ((nstring = mmalloc(sizeof(char) * (size_s1 + 2))) == NULL)
		return (NULL);
	i = 0;
	while (i < size_s1)
	{
		nstring[i] = s1[i];
		i++;
	}
	nstring[i] = c2;
	nstring[i + 1] = '\0';
	free_it2(&s1, free_level);
	return (nstring);
}
