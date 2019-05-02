/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flat_top_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 03:33:20 by cababou           #+#    #+#             */
/*   Updated: 2019/05/02 01:30:04 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

Uint32	tile_color(int block_type)
{
	if (block_type == block_wall)
		return (0xFF848484);
	else if (block_type == block_air)
		return (0xFFFFFEDD);
	else if (block_type == block_small_wall)
		return (0xFFb78c73);
	else
		return (0xFF000000);
}

void	editor_ftr_brender(t_doom *doom)
{
	t_editor	*e;

	e = &doom->editor;
	draw_rect_u(e->flat_top_render, make_rect(0, 0, e->flat_top_render_rect.w,
		e->flat_top_render_rect.h), 0xFF000000, 1);
	editor_ftr_mrender(doom);
	draw_rect_u(e->flat_top_render, make_rect(0, 0, e->flat_top_render_rect.w,
		e->flat_top_render_rect.h), 0xFF000000, 0);
	SDL_BlitSurface(e->flat_top_render, NULL, doom->editor.ed_surface, &e->flat_top_render_rect);
}

void	editor_ftr_mrender(t_doom *doom)
{
	t_quadrant_renderer	*q;
	SDL_Rect			m_pos;
	size_t				x;
	size_t				y;
	SDL_Rect			r;

	q = &doom->editor.flat_top_quadrant;
	m_pos = mouse_pos();
	x = 0;
	while (x < doom->nmap->size_x)
	{
		y = 0;
		while (y < doom->nmap->size_y)
		{
			r = make_rect(q->x_start + x * q->zoom_level, q->y_start + y * q->zoom_level, q->zoom_level, q->zoom_level);
			draw_rect_u(doom->editor.flat_top_render, r, tile_color(doom->nmap->map[x][y].block_type), 1);
			if (mouse_in(m_pos.x - q->pos_x, m_pos.y - q->pos_y, r))
				draw_rect_u(doom->editor.flat_top_render, r, 0xFF000000, 0);
			y++;
		}
		x++;
	}
}