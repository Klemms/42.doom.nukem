/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_next_sqrt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 12:07:13 by lde-batz          #+#    #+#             */
/*   Updated: 2018/12/01 12:07:50 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_next_sqrt(int nb, char sign)
{
	int test;

	test = 0;
	if (nb < 0)
		return (0);
	while (test * test < nb)
		test++;
	if (test * test == nb || sign == '+')
		return (test);
	if (sign == '-')
		return (test - 1);
	else
		return (0);
}
