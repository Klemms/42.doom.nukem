/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 17:39:12 by lde-batz          #+#    #+#             */
/*   Updated: 2018/11/15 17:40:07 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sqrt(int nb)
{
	int test;

	test = 0;
	if (nb < 0)
		return (0);
	while (test * test < nb)
		test++;
	if (test * test == nb)
		return (test);
	else
		return (0);
}
