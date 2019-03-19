/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:08:25 by lde-batz          #+#    #+#             */
/*   Updated: 2018/11/10 12:47:43 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int				i;
	long long int	ret;
	int				neg;

	i = 0;
	ret = 0;
	neg = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == 43 || nptr[i] == 45)
		(nptr[i++] == 45) ? neg = 1 : neg;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		ret = ret * 10 + (nptr[i++] - 48);
	(neg == 1) ? ret = -ret : ret;
	return (ret);
}
