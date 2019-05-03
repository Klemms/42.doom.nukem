/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkbox.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 03:48:04 by cababou           #+#    #+#             */
/*   Updated: 2019/05/03 08:28:11 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_el_checkbox	*create_checkbox(t_doom *d, SDL_Rect pos, int checked)
{
	t_el_checkbox	*ck;

	if (!(ck = mmalloc(sizeof(t_el_checkbox))))
		exit_program(d, ERROR_SDL_AFTER_INIT);
	ck->pos = pos;
	ck->disabled_c = make_rgb(50, 50, 50, 255);
	ck->background = make_rgb(190, 190, 190, 255);
	ck->border = d->editor.base_color;
	ck->color = d->editor.select_color;
	ck->checked = 0;
	ck->disabled = 0;
	return (ck);
}

void		checkbox_render(t_doom *d, SDL_Surface *s, t_el_checkbox *ck)
{
	draw_rect(s, ck->pos, ck->disabled ? ck->disabled_c : ck->background, 1);
	if (ck->checked)
		draw_rect(s, make_rect(ck->pos.x + ck->pos.w / 4, ck->pos.y + ck->pos.w
				/ 4, ck->pos.w - ck->pos.w / 2, ck->pos.h - ck->pos.w / 2),
			ck->color, 1);
	draw_rect(s, ck->pos, ck->border, 0);
}
