/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsubuntilchar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 07:13:45 by cababou           #+#    #+#             */
/*   Updated: 2018/04/13 01:29:50 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsubuntilchar(char const *str, size_t start, char end_char)
{
	char	*newstring;
	size_t	i;

	newstring = ft_strnew(0);
	i = start;
	while (str[i] != end_char || str[i])
	{
		newstring = ft_strjoin(newstring, ft_strsub(str, i, i + 1, 0), 1);
		i++;
	}
	return (newstring);
}
