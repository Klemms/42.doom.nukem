/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flat_top_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 03:33:20 by cababou           #+#    #+#             */
/*   Updated: 2019/05/02 05:38:48 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "editor.h"

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
	int					x;
	int					y;
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
			{
				//draw_rect_u(doom->editor.flat_top_render, r, 0xFF000000, 0);
			}
			y++;
		}
		x++;
	}
	x = (int)((m_pos.x - q->pos_x - q->x_start) / q->zoom_level);
	y = (int)((m_pos.y - q->pos_y - q->y_start) / q->zoom_level);
	if (m_pos.x - q->pos_x - q->x_start >= 0 && m_pos.y - q->pos_y - q->y_start >= 0)
	{
		r = make_rect(q->x_start + x * q->zoom_level, q->y_start + y * q->zoom_level, q->zoom_level, q->zoom_level);
		draw_rect_u(doom->editor.flat_top_render, r, doom->editor.selected_block ?
			doom->editor.selected_block->block_color : 0xFFFF0000, 0);
		doom->editor.x_focus = x;
		doom->editor.y_focus = y;
	}
}

void	editor_ftr_clicked(t_doom *doom)
{
	t_editor	*e;	

	e = &doom->editor;
	if (e->x_focus >= 0 && e->y_focus >= 0 && e->x_focus < doom->nmap->size_x
		&& e->y_focus < doom->nmap->size_y && e->selected_block >= 0
		&& e->selected_block && doom->editor.hand_tool == tool_block)
	{
		doom->nmap->map[e->x_focus][e->y_focus].block_type = e->selected_block->block_type;
	}
}
