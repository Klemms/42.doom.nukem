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
		if (b->ui->id == doom->editor.rbr_quadrant.orient_hor->ui->id)
			doom->editor.foc.b_orientation = 0;
		if (b->ui->id == doom->editor.rbr_quadrant.orient_ver->ui->id)
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
	if (e->selected_block)
	{
		doom->tmp_color = make_rgb(0, 0, 0, 255);
		instant_text(doom, e->rbr, ft_strjoin("Block : ", e->selected_block->block_name, 0), make_rect(10, 10, 22, 1));
		instant_text(doom, e->rbr, "Block orientation", make_rect(10, 45, 20, 0));
		e->rbr_quadrant.orient_hor->background_color = e->foc.b_orientation == 0 ? e->select_color : e->base_color;
		button_render(doom, e->rbr, e->rbr_quadrant.orient_hor);
		e->rbr_quadrant.orient_ver->background_color = e->foc.b_orientation == 1 ? e->select_color : e->base_color;
		button_render(doom, e->rbr, e->rbr_quadrant.orient_ver);
		e->rbr_quadrant.orient_w->background_color = e->foc.b_orientation == 2 ? e->select_color : e->base_color;
		button_render(doom, e->rbr, e->rbr_quadrant.orient_w);
		e->rbr_quadrant.orient_e->background_color = e->foc.b_orientation == 3 ? e->select_color : e->base_color;
		button_render(doom, e->rbr, e->rbr_quadrant.orient_e);
		instant_text(doom, e->rbr, "Block height", make_rect(10, 155, 20, 0));
		wjauge_render(doom, e->rbr, e->rbr_quadrant.s_height);
		instant_text(doom, e->rbr, "Ceiling height", make_rect(10, 230, 20, 0));
		wjauge_render(doom, e->rbr, e->rbr_quadrant.sc_height);
		instant_text(doom, e->rbr, "Has ceiling", make_rect(10, 310, 20, 0));
		checkbox_render(doom, e->rbr, e->rbr_quadrant.has_celng);
		instant_text(doom, e->rbr, "Block x-size", make_rect(10, 345, 20, 0));
		wjauge_render(doom, e->rbr, e->rbr_quadrant.b_w);
		instant_text(doom, e->rbr, "Block y-size", make_rect(10, 420, 20, 0));
		wjauge_render(doom, e->rbr, e->rbr_quadrant.b_h);
	}
}

int		rbr_click(t_doom *d, SDL_Event event)
{
	SDL_MouseButtonEvent	ms;
	t_quadrant_renderer		*qr;
	SDL_Rect				rc;

	ms = event.button;
	qr = &d->editor.rbr_quadrant;
	if (ms.button == SDL_BUTTON_LEFT)
	{
		rc = make_rect(qr->pos_x + qr->has_celng->pos.x, qr->pos_y + qr->has_celng->pos.y, qr->has_celng->pos.w, qr->has_celng->pos.h);
		if (mouse_in(d->m_x, d->m_y, rc))
		{
			qr->has_celng->checked = !qr->has_celng->checked;
			d->editor.foc.b_ceiling_height = qr->has_celng->checked;
		}
	}
	return (1);
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
		d->editor.foc.b_height = qr->s_height->value;
	}
	rc = make_rect(qr->pos_x + qr->sc_height->pos.x, qr->pos_y + qr->sc_height->pos.y, qr->sc_height->pos.w, qr->sc_height->pos.h);
	if (mouse_in(d->m_x, d->m_y, rc))
	{
		wjauge_affect(d, qr->sc_height, wheel.y > 0 ? 1 : -1, 1);
		d->editor.foc.b_ceiling_height = qr->sc_height->value;
	}
	rc = make_rect(qr->pos_x + qr->b_w->pos.x, qr->pos_y + qr->b_w->pos.y, qr->b_w->pos.w, qr->b_w->pos.h);
	if (mouse_in(d->m_x, d->m_y, rc))
	{
		wjauge_affect(d, qr->b_w, wheel.y > 0 ? 1 : -1, 1);
		d->editor.foc.b_x_size = qr->b_w->value;
	}
	rc = make_rect(qr->pos_x + qr->b_h->pos.x, qr->pos_y + qr->b_h->pos.y, qr->b_h->pos.w, qr->b_h->pos.h);
	if (mouse_in(d->m_x, d->m_y, rc))
	{
		wjauge_affect(d, qr->b_h, wheel.y > 0 ? 1 : -1, 1);
		d->editor.foc.b_y_size = qr->b_h->value;
	}
	return (1);
}
