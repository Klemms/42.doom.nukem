/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 03:33:20 by cababou           #+#    #+#             */
/*   Updated: 2019/05/03 02:29:58 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "editor.h"

t_block_type	*block_type(t_doom *d, int bt)
{
	t_list			*tmp;
	t_block_type	*tmpbt;

	tmp = d->block_types->firstelement;
	while (tmp)
	{
		tmpbt = tmp->content;
		if (tmpbt->block_type == bt)
			return (tmpbt);
		tmp = tmp->next;
	}
	return (NULL);
}

void	editor_ftr_brender(t_doom *doom)
{
	t_editor	*e;

	e = &doom->editor;
	draw_rect_u(e->ftr, make_rect(0, 0, e->ftr_rect.w,
		e->ftr_rect.h), 0xFF333333, 1);
	editor_ftr_mrender(doom);
	draw_rect_u(e->ftr, make_rect(0, 0, e->ftr_rect.w,
		e->ftr_rect.h), 0xFF000000, 0);
	SDL_BlitSurface(e->ftr, NULL, doom->editor.ed_surface, &e->ftr_rect);
}

void	editor_ftr_mrender(t_doom *doom)
{
	t_quadrant_renderer	*q;
	SDL_Rect			m_pos;
	int					x;
	int					y;
	SDL_Rect			r;

	q = &doom->editor.ftr_quadrant;
	m_pos = mouse_pos();
	y = 0;
	while (y < doom->nmap->size_y)
	{
		x = 0;
		while (x < doom->nmap->size_x)
		{
			r = make_rect(q->x_start + x * q->zoom_level, q->y_start + y * q->zoom_level, q->zoom_level, q->zoom_level);
			draw_rect_u(doom->editor.ftr, r, block_type(doom, doom->nmap->map[y][x].block_type)->block_color, 1);
			/*if (mouse_in(m_pos.x - q->pos_x, m_pos.y - q->pos_y, r))
			{
				//draw_rect_u(doom->editor.ftr, r, 0xFF000000, 0);
			}*/
			x++;
		}
		y++;
	}
	doom->editor.x_focus = -1;
	doom->editor.y_focus = -1;
	x = (int)((m_pos.x - q->pos_x - q->x_start) / q->zoom_level);
	y = (int)((m_pos.y - q->pos_y - q->y_start) / q->zoom_level);
	if (m_pos.x - q->pos_x - q->x_start >= 0 && m_pos.y - q->pos_y - q->y_start >= 0)
	{
		r = make_rect(q->x_start + x * q->zoom_level, q->y_start + y * q->zoom_level, q->zoom_level, q->zoom_level);
		draw_rect_u(doom->editor.ftr, r, doom->editor.selected_block ?
			doom->editor.selected_block->block_color : 0xFFFF0000, 0);
		doom->editor.x_focus = x;
		doom->editor.y_focus = y;
	}
}

void	editor_ftr_clicked(t_doom *doom)
{
	t_editor	*e;	

	e = &doom->editor;
	if (e->selected_block && doom->editor.hand_tool == tool_block && e->selected_block >= 0)
	{
		if (e->x_focus >= 0 && e->y_focus >= 0 && e->x_focus < doom->nmap->size_x
			&& e->y_focus < doom->nmap->size_y)
		{
			if (e->selected_block->block_type != block_apply)
			{
				doom->nmap->map[e->y_focus][e->x_focus].block_type = e->selected_block->block_type;
				doom->nmap->map[e->y_focus][e->x_focus].collides = e->selected_block->block_type == block_wall || e->selected_block->block_type == block_sprite ? 1 : 0;
			}
		}
		else if (e->x_focus > 0 && e->y_focus > 0)
		{
			expand_map(doom, doom->nmap, new_block(doom, e->selected_block->block_type, e->x_focus, e->y_focus));
		}
	}
}
