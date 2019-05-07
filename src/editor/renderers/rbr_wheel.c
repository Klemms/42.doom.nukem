/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbr_wheel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 22:36:42 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/07 22:38:15 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "editor.h"

void	editor_rbr_mrender(t_doom *d)
{
	t_editor	*e;

	e = &d->editor;
	if (e->selected_block && e->selected_block->block_type != block_copy)
	{
		d->tmp_color = make_rgb(0, 0, 0, 255);
		instant_text(d, e->rbr, ft_strjoin("Block : ",
				e->selected_block->block_name, 0), make_rect(10, 10, 22, 1));
		instant_text(d, e->rbr, "Block orientation", make_rect(10, 45, 20, 0));
		e->rbr_quadrant.orient_hor->background_color = e->foc.b_orientation
			== 0 ? e->select_color : e->base_color;
		button_render(d, e->rbr, e->rbr_quadrant.orient_hor);
		e->rbr_quadrant.orient_ver->background_color = e->foc.b_orientation
			== 1 ? e->select_color : e->base_color;
		edit_button_render(d, e);
	}
}

int		rbr_click(t_doom *d, SDL_Event event)
{
	SDL_MouseButtonEvent	ms;
	t_quadrant_renderer		*qr;
	SDL_Rect				rc;

	ms = event.button;
	qr = &d->editor.rbr_quadrant;
	if (ms.button == SDL_BUTTON_LEFT && d->editor.selected_block)
	{
		rc = make_rect(qr->pos_x + qr->has_celng->pos.x, qr->pos_y
		+ qr->has_celng->pos.y, qr->has_celng->pos.w, qr->has_celng->pos.h);
		if (mouse_in(d->m_x, d->m_y, rc))
		{
			qr->has_celng->checked = !qr->has_celng->checked;
			d->editor.foc.b_ceiling_height = qr->has_celng->checked;
		}
	}
	return (1);
}

void	rbr_wheel2(t_doom *d, t_quadrant_renderer *qr,
	SDL_MouseWheelEvent wheel, SDL_Rect rc)
{
	rc = make_rect(qr->pos_x + qr->b_w->pos.x, qr->pos_y
		+ qr->b_w->pos.y, qr->b_w->pos.w, qr->b_w->pos.h);
	if (mouse_in(d->m_x, d->m_y, rc))
	{
		wjauge_affect(d, qr->b_w, wheel.y > 0 ? 1 : -1, 1);
		d->editor.foc.b_x_size = qr->b_w->value;
	}
	rc = make_rect(qr->pos_x + qr->b_h->pos.x, qr->pos_y
		+ qr->b_h->pos.y, qr->b_h->pos.w, qr->b_h->pos.h);
	if (mouse_in(d->m_x, d->m_y, rc))
	{
		wjauge_affect(d, qr->b_h, wheel.y > 0 ? 1 : -1, 1);
		d->editor.foc.b_y_size = qr->b_h->value;
	}
}

int		rbr_wheel(t_doom *d, SDL_Event event)
{
	SDL_MouseWheelEvent	wheel;
	t_quadrant_renderer	*qr;
	SDL_Rect			rc;

	wheel = event.wheel;
	qr = &d->editor.rbr_quadrant;
	rc = make_rect(qr->pos_x + qr->ev_id->pos.x, qr->pos_y
		+ qr->ev_id->pos.y, qr->ev_id->pos.w, qr->ev_id->pos.h);
	if (mouse_in(d->m_x, d->m_y, rc))
	{
		wjauge_affect(d, qr->ev_id, wheel.y > 0 ? 1 : -1, 1);
		d->editor.foc.b_event_id = qr->ev_id->value;
	}
	rc = make_rect(qr->pos_x + qr->sc_height->pos.x, qr->pos_y
		+ qr->sc_height->pos.y, qr->sc_height->pos.w, qr->sc_height->pos.h);
	if (mouse_in(d->m_x, d->m_y, rc))
	{
		wjauge_affect(d, qr->sc_height, wheel.y > 0 ? 1 : -1, 1);
		d->editor.foc.b_ceiling_height = qr->sc_height->value;
	}
	rbr_wheel2(d, qr, wheel, rc);
	return (1);
}
