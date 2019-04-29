/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 19:20:19 by cababou           #+#    #+#             */
/*   Updated: 2019/04/05 12:25:31 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char const *s1)
{
	size_t	i;
	char	*nstring;

	nstring = mmalloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (nstring == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		nstring[ft_strlen(s1) - i - 1] = s1[i];
		i++;
	}
	nstring[i] = '\0';
	return (nstring);
}
