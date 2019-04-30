/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 04:45:58 by cababou           #+#    #+#             */
/*   Updated: 2019/04/19 04:48:07 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		button_coords_contained(t_el_button *button, int x, int y)
{
	if (x >= button->rect.x && x <= (button->rect.x + button->rect.w))
		if (y >= button->rect.y && y <= (button->rect.y + button->rect.h))
			return (1);
	return (0);
}
