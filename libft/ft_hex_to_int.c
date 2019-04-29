/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_to_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 02:56:09 by cababou           #+#    #+#             */
/*   Updated: 2019/04/05 12:29:13 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_hex_to_int(char *hex, int free_it)
{
	size_t	i;
	int		multi;
	int		nbr;

	multi = ft_strlen(hex) - 1;
	nbr = 0;
	i = 0;
	while (hex[i])
	{
		nbr += letter_to_int(hex[i]) * ft_pow(16, multi);
		multi--;
		i++;
	}
	if (free_it == 1)
		ffree(hex);
	return (nbr);
}
