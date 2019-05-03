/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 02:19:34 by cababou           #+#    #+#             */
/*   Updated: 2019/05/03 04:53:37 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "editor.h"

void	ed_bt_edit_click(t_doom *doom, t_el_button *b, SDL_MouseButtonEvent ev)
{
	if (ev.button == SDL_BUTTON_LEFT)
	{
		if (b->ui->id == doom->editor.rbr_quadrant.orient_n->ui->id)
			doom->editor.foc.b_orientation = 0;
		if (b->ui->id == doom->editor.rbr_quadrant.orient_s->ui->id)
			doom->editor.foc.b_orientation = 1;
		if (b->ui->id == doom->editor.rbr_quadrant.orient_w->ui->id)
			doom->editor.foc.b_orientation = 2;
		if (b->ui->id == doom->editor.rbr_quadrant.orient_e->ui->id)
			doom->editor.foc.b_orientation = 3;
	}
}

void	editor_rbr_brender(t_doom *doom)
{
	t_editor	*e;

	e = &doom->editor;
	draw_rect_u(e->rbr, make_rect(0, 0, e->rbr_rect.w,
		e->rbr_rect.h), 0xFFd4d5d8, 1);
	editor_rbr_mrender(doom);
	SDL_BlitSurface(e->rbr, NULL, doom->editor.ed_surface, &e->rbr_rect);
}

void	editor_rbr_mrender(t_doom *doom)
{
	t_editor	*e;

	e = &doom->editor;
	/*if (e->selected_block)
	{*/
		doom->temp_color = 0xFF000000;
		instant_text(doom, e->rbr, "Block orientation", make_rect(10, 10, 20, 0));
		e->rbr_quadrant.orient_n->background_color = e->foc.b_orientation == 0 ? e->select_color : e->base_color;
		button_render(doom, e->rbr, e->rbr_quadrant.orient_n);
		e->rbr_quadrant.orient_s->background_color = e->foc.b_orientation == 1 ? e->select_color : e->base_color;
		button_render(doom, e->rbr, e->rbr_quadrant.orient_s);
		e->rbr_quadrant.orient_w->background_color = e->foc.b_orientation == 2 ? e->select_color : e->base_color;
		button_render(doom, e->rbr, e->rbr_quadrant.orient_w);
		e->rbr_quadrant.orient_e->background_color = e->foc.b_orientation == 3 ? e->select_color : e->base_color;
		button_render(doom, e->rbr, e->rbr_quadrant.orient_e);
		wjauge_render(doom, e->rbr, e->rbr_quadrant.s_height);
	//}
}

int		rbr_wheel(t_doom *d, SDL_Event event)
{
	SDL_MouseWheelEvent	wheel;
	t_quadrant_renderer	*qr;
	SDL_Rect			rc;

	wheel = event.wheel;
	qr = &d->editor.rbr_quadrant;
	rc = make_rect(qr->pos_x + qr->s_height->pos.x, qr->pos_y + qr->s_height->pos.y, qr->s_height->pos.w, qr->s_height->pos.h);
	if (mouse_in(d->m_x, d->m_y, rc))
	{
		wjauge_affect(d, qr->s_height, wheel.y > 0 ? 1 : -1, 1);
	}
	return (1);
}
