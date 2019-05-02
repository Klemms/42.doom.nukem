/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bottom_select_render.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 03:50:06 by cababou           #+#    #+#             */
/*   Updated: 2019/05/02 06:40:51 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "editor.h"

void	render_blocks(t_doom *doom)
{
	t_list			*tmp;
	t_block_type	*tmp_bt;
	int				x;
	int				y;

	doom->tmp_color = make_rgb(255, 255, 255, 255);
	instant_text(doom, doom->editor.bottom_select_render,
		"Block list", make_rect(20, 10, 25, 0));
	tmp = doom->editor.block_types->firstelement;
	x = 10;
	y = 50;
	while (tmp)
	{
		tmp_bt = (t_block_type *)tmp->content;
		draw_rect_u(doom->editor.bottom_select_render, make_rect(x, y, 170, 70),
			tmp_bt->block_color, 1);
		doom->tmp_color = make_rgb(0, 0, 0, 255);
		instant_text(doom, doom->editor.bottom_select_render,
			tmp_bt->block_name, make_rect(x + 10, y + 22, 20, 0));
		if (is_left_clicking() && mouse_in(doom->m_x, doom->m_y, make_rect(doom->editor.bottom_select_render_rect.x + x, doom->editor.bottom_select_render_rect.y + y, 170, 70)))
		{
			doom->editor.selected_block = tmp_bt;
		}
		x += 180;
		if (x + 180 >= doom->editor.bottom_select_render_rect.w)
		{
			x = 10;
			y += 80;
		}
		tmp = tmp->next;
	}
}

void	editor_bsr_clicked(t_doom *doom)
{
	
}

void	editor_bsr_brender(t_doom *doom)
{
	t_editor	*e;

	e = &doom->editor;
	draw_rect_u(e->bottom_select_render, make_rect(0, 0,
			e->bottom_select_render_rect.w, e->bottom_select_render_rect.h),
		0xFF626468, 1);
	editor_bsr_mrender(doom);
	draw_rect_u(e->bottom_select_render, make_rect(0, 0,
			e->bottom_select_render_rect.w, e->bottom_select_render_rect.h),
		0xFF000000, 0);
	SDL_BlitSurface(e->bottom_select_render, NULL, doom->editor.ed_surface,
		&e->bottom_select_render_rect);
}

void	editor_bsr_mrender(t_doom *doom)
{
	if (doom->editor.hand_tool == tool_block)
	{
		render_blocks(doom);
	}
}
