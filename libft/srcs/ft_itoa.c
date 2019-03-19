/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 11:26:07 by lde-batz          #+#    #+#             */
/*   Updated: 2018/11/14 18:29:29 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_itoa_cptnbr(long int n)
{
	int len;

	len = 0;
	if (n < 0)
		len++;
	if (n == 0)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	int			i;
	long int	ncpy;
	char		*res;

	ncpy = n;
	i = ft_itoa_cptnbr(ncpy);
	if (!(res = (char*)malloc(sizeof(*res) * (i + 1))))
		return (NULL);
	res[i] = '\0';
	i--;
	if (ncpy < 0)
	{
		res[0] = '-';
		ncpy = -ncpy;
	}
	if (ncpy == 0)
		res[0] = '0';
	while (ncpy != 0)
	{
		res[i] = '0' + (ncpy % 10);
		ncpy = ncpy / 10;
		i--;
	}
	return (res);
}
