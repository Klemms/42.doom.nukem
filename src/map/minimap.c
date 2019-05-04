/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 10:59:23 by cababou           #+#    #+#             */
/*   Updated: 2019/05/04 11:00:29 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	draw_minimap(t_doom *d)
{
	t_quadrant_renderer	*q;
	int					x;
	int					y;
	SDL_Rect			r;

	q = &d->editor.ftr_quadrant;
	y = 0;
	while (y < d->nmap->size_y)
	{
		x = 0;
		while (x < d->nmap->size_x)
		{
			r = make_rect(100 + x * 15, 100 + y * 15, 15, 15);
			draw_rect_u(d->surface, r, block_type(d, d->nmap->map[y][x].block_type)->block_color, 1);
			x++;
		}
		y++;
	}	
	draw_rect_u(d->surface, make_rect(100 + d->you.pos.x * 15, 100 + d->you.pos.y * 15, 5, 5), 0xFFFF0000, 1);
}
