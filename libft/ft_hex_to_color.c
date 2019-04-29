/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_to_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 02:51:37 by cababou           #+#    #+#             */
/*   Updated: 2019/04/05 12:29:07 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_hex_to_color(char *hex, int free_it)
{
	int r;
	int g;
	int b;

	if (hex == NULL)
		return (0);
	r = ft_hex_to_int(ft_strsub(hex, 2, 2, 0), 1);
	g = ft_hex_to_int(ft_strsub(hex, 4, 2, 0), 1);
	b = ft_hex_to_int(ft_strsub(hex, 6, 2, 0), 1);
	if (free_it == 1)
		ffree(hex);
	return (rgba_to_int(r, g, b, 0));
}
