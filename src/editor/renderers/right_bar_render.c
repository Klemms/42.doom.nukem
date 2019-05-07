/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_bar_render.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 22:41:31 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/07 22:41:35 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "editor.h"

void	ed_bt_edit_click(t_doom *d, t_el_button *b, SDL_MouseButtonEvent ev)
{
	if (ev.button == SDL_BUTTON_LEFT)
	{
		if (b->ui->id == d->editor.rbr_quadrant.orient_hor->ui->id)
			d->editor.foc.b_orientation = 0;
		if (b->ui->id == d->editor.rbr_quadrant.orient_ver->ui->id)
			d->editor.foc.b_orientation = 1;
		if (b->ui->id == d->editor.rbr_quadrant.texture_n->ui->id)
			d->editor.texture_edited = 0;
		if (b->ui->id == d->editor.rbr_quadrant.texture_n->ui->id)
			switch_tool(d, tool_textures, NULL);
		if (b->ui->id == d->editor.rbr_quadrant.texture_s->ui->id)
			d->editor.texture_edited = 1;
		if (b->ui->id == d->editor.rbr_quadrant.texture_s->ui->id)
			switch_tool(d, tool_textures, NULL);
		if (b->ui->id == d->editor.rbr_quadrant.texture_w->ui->id)
			d->editor.texture_edited = 2;
		if (b->ui->id == d->editor.rbr_quadrant.texture_w->ui->id)
			switch_tool(d, tool_textures, NULL);
		if (b->ui->id == d->editor.rbr_quadrant.texture_e->ui->id)
			d->editor.texture_edited = 3;
		if (b->ui->id == d->editor.rbr_quadrant.texture_e->ui->id)
			switch_tool(d, tool_textures, NULL);
	}
}

void	editor_rbr_brender(t_doom *d)
{
	t_editor	*e;

	e = &d->editor;
	draw_rect_u(e->rbr, make_rect(0, 0, e->rbr_rect.w,
		e->rbr_rect.h), 0xFFd4d5d8, 1);
	if (d->editor.hand_tool == tool_sprite)
		editor_rbrs_mrender(d);
	if (d->editor.hand_tool == tool_block)
		editor_rbr_mrender(d);
	if (d->editor.hand_tool == tool_sprite && !d->editor.selected_sprite)
		ed_sprite_list(d);
	SDL_BlitSurface(e->rbr, NULL, d->editor.ed_surface, &e->rbr_rect);
}

void	edit_button_render(t_doom *d, t_editor *e)
{
	button_render(d, e->rbr, e->rbr_quadrant.orient_ver);
	instant_text(d, e->rbr, "Event ID", make_rect(10, 155, 20, 0));
	wjauge_render(d, e->rbr, e->rbr_quadrant.ev_id);
	instant_text(d, e->rbr, "Ceiling height", make_rect(10, 230, 20, 0));
	wjauge_render(d, e->rbr, e->rbr_quadrant.sc_height);
	instant_text(d, e->rbr, "Has ceiling", make_rect(10, 310, 20, 0));
	checkbox_render(d, e->rbr, e->rbr_quadrant.has_celng);
	instant_text(d, e->rbr, "Block x-size", make_rect(10, 345, 20, 0));
	wjauge_render(d, e->rbr, e->rbr_quadrant.b_w);
	instant_text(d, e->rbr, "Block y-size", make_rect(10, 420, 20, 0));
	wjauge_render(d, e->rbr, e->rbr_quadrant.b_h);
	button_render_texture(d, e->rbr, e->rbr_quadrant.texture_n,
		get_surface(d, e->foc.b_n_texture));
	button_render_texture(d, e->rbr, e->rbr_quadrant.texture_s,
		get_surface(d, e->foc.b_s_texture));
	button_render_texture(d, e->rbr, e->rbr_quadrant.texture_w,
		get_surface(d, e->foc.b_w_texture));
	button_render_texture(d, e->rbr, e->rbr_quadrant.texture_e,
		get_surface(d, e->foc.b_e_texture));
}
