/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 11:35:56 by lde-batz          #+#    #+#             */
/*   Updated: 2019/03/19 12:04:03 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *nptr)
{
	int		i;
	int		j;
	double	ret;
	double	rest;
	int		neg;

	i = 0;
	j = 0;
	ret = 0.0;
	rest = 0.0;
	neg = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == 43 || nptr[i] == 45)
		(nptr[i++] == 45) ? neg = 1 : neg;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		ret = ret * 10 + (nptr[i++] - 48);
	i++;
	j = i;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		rest = rest * 10 + (nptr[i++] - 48);
	ret += rest * pow(10, j - i);
	(neg == 1) ? ret = -ret : ret;
	return (ret);
}
