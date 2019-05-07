/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_bar_render_sprite.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 15:59:11 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 20:28:40 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "editor.h"

void	ed_sprite_list(t_doom *d)
{
	t_sprite_type	*type;
	t_list			*tmp;
	t_sprite		*tmp_sprite;
	size_t			y;
	SDL_Rect		r;

	tmp = d->nmap->sprites->firstelement;
	y = 15;
	while (tmp)
	{
		tmp_sprite = tmp->content;
		type = get_sprite_type(d, tmp_sprite->type);
		d->tmp_color = make_rgb(0, 0, 0, 255);
		r = make_rect(10, y, 280, 23);
		draw_rect_u(d->editor.rbr, r, 0xFFAAAAAA, 1);
		instant_text(d, d->editor.rbr, ft_strdup(type->sprite_name),
				make_rect(15, y + 2, 15, 1));
		r = make_rect(d->editor.rbr_quadrant.pos_x + 10, d->editor.rbr_quadrant.pos_y + y, 280, 23);
		if (mouse_in(d->m_x, d->m_y, r))
		{
			r = make_rect(d->editor.ftr_quadrant.x_start + tmp_sprite->base_x * d->editor.ftr_quadrant.zoom_level, d->editor.ftr_quadrant.y_start + tmp_sprite->base_y * d->editor.ftr_quadrant.zoom_level, d->editor.ftr_quadrant.zoom_level / 2, d->editor.ftr_quadrant.zoom_level / 2);
			draw_rect_u(d->editor.ftr, r, type->sprite_color, 1);
			SDL_BlitSurface(d->editor.ftr, NULL, d->editor.ed_surface, &d->editor.ftr_rect);
			if (is_left_clicking())
			{
				remove_sprite(d, tmp);
				break;
			}
		}
		y += 28;
		tmp = tmp->next;
	}
}

void	editor_rbrs_mrender(t_doom *d)
{
	t_editor	*e;

	e = &d->editor;
	if (e->selected_sprite)
	{
		d->tmp_color = make_rgb(0, 0, 0, 255);
		instant_text(d, e->rbr, ft_strjoin("Sprite : ", e->selected_sprite->sprite_name, 0), make_rect(10, 10, 22, 1));
		button_render_texture(d, e->rbr, e->rbr_quadrant.texture_n, get_surface(d, e->foc_s.b_texture));
		button_render_texture(d, e->rbr, e->rbr_quadrant.texture_s, get_surface(d, e->foc_s.b_texture_back));
		instant_text(d, e->rbr, ft_strdup("Has collision"), make_rect(10, 50, 19, 1));
		checkbox_render(d, e->rbr, e->rbr_quadrant.sp_collides);
		instant_text(d, e->rbr, ft_strdup("Is obtainable"), make_rect(10, 90, 19, 1));
		checkbox_render(d, e->rbr, e->rbr_quadrant.sp_obtainable);
	}
}

int		rbrs_click(t_doom *d, SDL_Event event)
{
	SDL_MouseButtonEvent	ms;
	t_quadrant_renderer		*qr;
	SDL_Rect				rc;

	ms = event.button;
	qr = &d->editor.rbr_quadrant;
	if (ms.button == SDL_BUTTON_LEFT && d->editor.selected_sprite)
	{
		rc = make_rect(qr->pos_x + qr->sp_collides->pos.x, qr->pos_y + qr->sp_collides->pos.y, qr->sp_collides->pos.w, qr->sp_collides->pos.h);
		if (mouse_in(d->m_x, d->m_y, rc))
		{
			qr->sp_collides->checked = !qr->sp_collides->checked;
			d->editor.foc_s.b_collides = qr->sp_collides->checked;
		}
		rc = make_rect(qr->pos_x + qr->sp_obtainable->pos.x, qr->pos_y + qr->sp_obtainable->pos.y, qr->sp_obtainable->pos.w, qr->sp_obtainable->pos.h);
		if (mouse_in(d->m_x, d->m_y, rc))
		{
			qr->sp_obtainable->checked = !qr->sp_obtainable->checked;
			d->editor.foc_s.b_obtainable = qr->sp_obtainable->checked;
		}
	}
	return (1);
}
