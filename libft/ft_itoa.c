/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 19:08:52 by cababou           #+#    #+#             */
/*   Updated: 2019/05/04 00:49:11 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	charsize(int n)
{
	size_t	size;

	if (n == 0)
		return (1);
	size = 0;
	if (n < 0)
	{
		n = n * -1;
		size++;
	}
	while (n > 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

char			*ft_itoa(int n)
{
	size_t		i;
	size_t		nsize;
	char		*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = 0;
	nsize = charsize(n);
	str = mmalloc(sizeof(char) * (nsize + 1));
	if (str == NULL)
		return (NULL);
	str[nsize] = '\0';
	if (n < 0)
	{
		str[nsize - 1] = '-';
		n = n * -1;
		nsize--;
	}
	while (i < nsize)
	{
		str[i] = '0' + (n % 10);
		n = n / 10;
		i++;
	}
	return (ft_strrev(str, 1));
}
