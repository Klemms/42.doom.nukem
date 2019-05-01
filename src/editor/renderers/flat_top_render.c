/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flat_top_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 03:33:20 by cababou           #+#    #+#             */
/*   Updated: 2019/05/01 05:10:51 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

Uint32	tile_color(char	tile)
{
	if (tile == '#')
		return (0xFFFF0000);
	else if (tile == '.')
		return (0xFF00FF00);
	else if (tile == 'T')
		return (0xFF0000FF);
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
	t_editor			*e;
	size_t				x;
	size_t				y;

	e = &doom->editor;
	q = &e->flat_top_quadrant;
	x = 0;
	while (doom->map.m[x])
	{
		y = 0;
		while (doom->map.m[x][y])
		{
			draw_rect_u(e->flat_top_render, make_rect(q->x_start + x * q->zoom_level, q->y_start + y * q->zoom_level, q->zoom_level, q->zoom_level), tile_color(doom->map.m[x][y]), 1);
			y++;
		}
		x++;
	}
}