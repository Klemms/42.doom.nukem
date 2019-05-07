/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbs_click.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 22:36:42 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/07 22:40:08 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "editor.h"

void	rbrs_click_apply(t_doom *d, SDL_Event event, SDL_MouseButtonEvent ms)
{
	t_quadrant_renderer		*qr;
	SDL_Rect				rc;

	qr = &d->editor.rbr_quadrant;
	(void)event;
	if (ms.button == SDL_BUTTON_LEFT && d->editor.selected_sprite)
	{
		rc = make_rect(qr->pos_x + qr->sp_collides->pos.x, qr->pos_y
			+ qr->sp_collides->pos.y, qr->sp_collides->pos.w,
			qr->sp_collides->pos.h);
		if (mouse_in(d->m_x, d->m_y, rc))
		{
			qr->sp_collides->checked = !qr->sp_collides->checked;
			d->editor.foc_s.b_collides = qr->sp_collides->checked;
		}
		rc = make_rect(qr->pos_x + qr->sp_obtainable->pos.x, qr->pos_y
			+ qr->sp_obtainable->pos.y, qr->sp_obtainable->pos.w,
			qr->sp_obtainable->pos.h);
		if (mouse_in(d->m_x, d->m_y, rc))
		{
			qr->sp_obtainable->checked = !qr->sp_obtainable->checked;
			d->editor.foc_s.b_obtainable = qr->sp_obtainable->checked;
		}
	}
}

int		rbrs_click(t_doom *d, SDL_Event event)
{
	SDL_MouseButtonEvent	ms;

	ms = event.button;
	rbrs_click_apply(d, event, ms);
	return (1);
}
