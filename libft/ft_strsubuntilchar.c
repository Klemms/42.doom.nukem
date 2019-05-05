/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsubuntilchar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 07:13:45 by cababou           #+#    #+#             */
/*   Updated: 2019/05/05 09:55:39 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsubuntilchar(char *str, size_t start, char end, int freet)
{
	char	*newstring;
	size_t	i;

	i = start;
	while (str[i] != end && str[i])
		i++;
	newstring = ft_strsub(str, start, i - start, freet);
	return (newstring);
}
