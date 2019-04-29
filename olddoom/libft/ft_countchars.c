/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countchars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 16:35:19 by cababou           #+#    #+#             */
/*   Updated: 2017/12/13 16:36:36 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_countchars(char const *s, char c)
{
	size_t	i;
	size_t	occurences;

	i = 0;
	occurences = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			occurences++;
		i++;
	}
	return (occurences);
}
