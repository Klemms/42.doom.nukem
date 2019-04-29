/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 16:34:05 by cababou           #+#    #+#             */
/*   Updated: 2019/04/05 12:25:05 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*scopy;
	int		i;

	if (s1 == NULL)
		return (NULL);
	scopy = mmalloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (scopy == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		scopy[i] = s1[i];
		i++;
	}
	scopy[i] = '\0';
	return (scopy);
}
