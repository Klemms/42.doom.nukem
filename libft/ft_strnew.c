/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:57:07 by cababou           #+#    #+#             */
/*   Updated: 2019/05/06 02:29:42 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size, int bzero)
{
	char	*str;

	if (bzero)
	{
		if (!(str = mmalloc(sizeof(char) * (size + 1))))
			return (NULL);
	}
	else
	{
		if (!(str = malloc(sizeof(char) * (size + 1))))
			return (NULL);
	}
	str[size] = '\0';
	return (str);
}
