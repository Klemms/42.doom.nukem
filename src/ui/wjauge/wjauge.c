/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wjauge.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 05:50:34 by cababou           #+#    #+#             */
/*   Updated: 2019/05/03 09:00:14 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_el_wh_jauge	*create_wjauge(t_doom *d, SDL_Rect rc, SDL_Rect mmvs)
{
	t_el_wh_jauge	*jg;

	if (!(jg = mmalloc(sizeof(t_el_wh_jauge))))
		exit_program(d, ERROR_SDL_AFTER_INIT);
	jg->ui = create_ui_element(d);
	jg->pos = rc;
	jg->min = mmvs.x;
	jg->max = mmvs.y;
	jg->value = mmvs.w;
	jg->step = mmvs.h;
	jg->background = make_rgb(190, 190, 190, 255);
	jg->border = d->editor.base_color;
	jg->color = d->editor.select_color;
	jg->is_focused = 0;
	jg->unit = ft_strdup("%");
	jg->txt = create_text(d, ft_strjoin(ft_itoa(jg->value), jg->unit, 1), FONT_RIFFIC, 20);
	jg->txt->text_color = make_rgb(0, 0, 0, 255);
	jg->txt->ui->pos_x = jg->pos.x + jg->pos.w / 2 - jg->txt->u_w / 2;
	jg->txt->ui->pos_y = jg->pos.y + jg->pos.h / 2 - jg->txt->u_h / 2;
	text_prepare(d, jg->txt, 1);
	return (jg);
}

void		wjauge_prepare(t_doom *d, t_el_wh_jauge *jg)
{
	jg->txt->text = ft_strjoin(ft_itoa(jg->value), jg->unit, 1);
	text_prepare(d, jg->txt, 1);
	jg->txt->ui->pos_x = jg->pos.x + jg->pos.w / 2 - jg->txt->u_w / 2;
	jg->txt->ui->pos_y = jg->pos.y + jg->pos.h / 2 - jg->txt->u_h / 2;
	text_prepare(d, jg->txt, 1);
}

void		wjauge_render(t_doom *d, SDL_Surface *s, t_el_wh_jauge *jg)
{
	draw_rect(s, make_rect(jg->pos.x, jg->pos.y, jg->pos.w, jg->pos.h), jg->background, 1);
	draw_rect(s, make_rect(jg->pos.x, jg->pos.y, (float)(jg->value - jg->min)
		/ (jg->max - jg->min) * jg->pos.w, jg->pos.h), jg->color, 1);
	draw_rect(s, make_rect(jg->pos.x, jg->pos.y, jg->pos.w, jg->pos.h), jg->border, 0);
	text_render(d, s, jg->txt);
}

void		wjauge_affect(t_doom *d, t_el_wh_jauge *jg, int change, int prepare)
{
	wjauge_set(d, jg, jg->value + change, prepare);
}

void		wjauge_set(t_doom *d, t_el_wh_jauge *jg, int value, int prepare)
{
	jg->value = value;
	if (jg->value > jg->max)
		jg->value = jg->max;
	if (jg->value < jg->min)
		jg->value = jg->min;
	if (prepare)
		wjauge_prepare(d, jg);
}
