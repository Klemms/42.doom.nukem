/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsr.c                             :+:      :+:    :+:   */
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
	instant_text(doom, doom->editor.bsr,
		"Block list", make_rect(20, 10, 25, 0));
	tmp = doom->block_types->firstelement;
	x = 10;
	y = 50;
	while (tmp)
	{
		tmp_bt = (t_block_type *)tmp->content;
		draw_rect_u(doom->editor.bsr, make_rect(x, y, 170, 70),
			tmp_bt->block_color, 1);
		doom->tmp_color = make_rgb(0, 0, 0, 255);
		instant_text(doom, doom->editor.bsr,
			tmp_bt->block_name, make_rect(x + 10, y + 22, 20, 0));
		if (is_left_clicking() && mouse_in(doom->m_x, doom->m_y, make_rect(doom->editor.bsr_rect.x + x, doom->editor.bsr_rect.y + y, 170, 70)))
			select_block_type(doom, tmp_bt);
		x += 180;
		if (x + 180 >= doom->editor.bsr_rect.w)
		{
			x = 10;
			y += 80;
		}
		tmp = tmp->next;
	}
}

void	render_textures(t_doom *doom)
{
	t_list			*tmp;
	int				x;
	int				y;

	doom->tmp_color = make_rgb(255, 255, 255, 255);
	instant_text(doom, doom->editor.bsr,
		"Texture list", make_rect(20, 10, 25, 0));
	tmp = doom->editor.l_textures->firstelement;
	x = 10;
	y = 50;
	while (tmp)
	{
		draw_rect_u(doom->editor.bsr, make_rect(x, y, 170, 30),
			0xFF86f4ad, 1);
		doom->tmp_color = make_rgb(0, 0, 0, 255);
		instant_text(doom, doom->editor.bsr,
			tmp->content, make_rect(x + 10, y + 3, 20, 0));
		/*if (is_left_clicking() && mouse_in(doom->m_x, doom->m_y, make_rect(doom->editor.bsr_rect.x + x, doom->editor.bsr_rect.y + y, 170, 70)))
			select_block_type(doom, tmp_bt);*/
		x += 180;
		if (x + 180 >= doom->editor.bsr_rect.w)
		{
			x = 10;
			y += 40;
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
	draw_rect_u(e->bsr, make_rect(0, 0,
			e->bsr_rect.w, e->bsr_rect.h),
		0xFF626468, 1);
	editor_bsr_mrender(doom);
	draw_rect_u(e->bsr, make_rect(0, 0,
			e->bsr_rect.w, e->bsr_rect.h),
		0xFF000000, 0);
	SDL_BlitSurface(e->bsr, NULL, doom->editor.ed_surface,
		&e->bsr_rect);
}

void	editor_bsr_mrender(t_doom *doom)
{
	if (doom->editor.hand_tool == tool_block)
	{
		render_blocks(doom);
	}
	else if (doom->editor.hand_tool == tool_textures)
	{
		render_textures(doom);
	}
}
