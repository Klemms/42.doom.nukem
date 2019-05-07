/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 03:02:44 by cababou           #+#    #+#             */
/*   Updated: 2018/09/04 04:50:43 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_pow(int nb, int power)
{
	int i;
	int nbr;

	if (power == 0)
		return (1);
	nbr = nb;
	i = 1;
	while (i < power)
	{
		nbr *= nbr;
		i++;
	}
	return (nbr);
}
