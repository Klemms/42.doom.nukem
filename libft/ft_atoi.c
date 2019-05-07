/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 16:15:59 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 09:05:33 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(char *str, int freeit)
{
	size_t i;
	size_t nb;
	size_t finalmult;

	i = 0;
	finalmult = 1;
	nb = 0;
	while (str[i] == ' ' || str[i] == '\v' || str[i] == '\n' || str[i] == '\t'
			|| str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			finalmult = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (freeit)
		free(str);
	return (nb * finalmult);
}
