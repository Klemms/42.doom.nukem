/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_bar_render.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 02:19:34 by cababou           #+#    #+#             */
/*   Updated: 2019/05/03 03:34:04 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "editor.h"

void	ed_bt_edit_click(t_doom *doom, t_el_button *b, SDL_MouseButtonEvent ev)
{
	
}

void	editor_rbr_brender(t_doom *doom)
{
	t_editor	*e;

	e = &doom->editor;
	draw_rect_u(e->right_bar_render, make_rect(0, 0, e->right_bar_render_rect.w,
		e->right_bar_render_rect.h), 0xFFd4d5d8, 1);
	editor_rbr_mrender(doom);
	SDL_BlitSurface(e->right_bar_render, NULL, doom->editor.ed_surface, &e->right_bar_render_rect);
}

void	editor_rbr_mrender(t_doom *doom)
{
	t_editor	*e;

	e = &doom->editor;
	/*if (e->selected_block)
	{*/
		doom->temp_color = 0xFF000000;
		instant_text(doom, e->right_bar_render, "Block orientation", make_rect(10, 10, 20, 0));
		e->right_bar_quadrant.orient_n->background_color = e->foc.b_orientation == 0 ? e->select_color : e->base_color;
		button_render(doom, e->right_bar_render, e->right_bar_quadrant.orient_n);
		e->right_bar_quadrant.orient_s->background_color = e->foc.b_orientation == 1 ? e->select_color : e->base_color;
		button_render(doom, e->right_bar_render, e->right_bar_quadrant.orient_s);
		e->right_bar_quadrant.orient_w->background_color = e->foc.b_orientation == 2 ? e->select_color : e->base_color;
		button_render(doom, e->right_bar_render, e->right_bar_quadrant.orient_w);
		e->right_bar_quadrant.orient_e->background_color = e->foc.b_orientation == 3 ? e->select_color : e->base_color;
		button_render(doom, e->right_bar_render, e->right_bar_quadrant.orient_e);
	//}
}
