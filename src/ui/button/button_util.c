/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 04:45:58 by cababou           #+#    #+#             */
/*   Updated: 2019/05/03 05:19:53 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		button_coords_contained(t_el_button *button, int x, int y)
{
	if (x >= button->real_x && x <= (button->real_x + button->rect.w))
		if (y >= button->real_y && y <= (button->real_y + button->rect.h))
			return (1);
	return (0);
}

void	add_button_rcoords(t_el_button *but, int x, int y)
{
	but->real_x += x;
	but->real_y += y;
}
