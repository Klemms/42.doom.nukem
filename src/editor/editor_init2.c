/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_init2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 22:57:58 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/07 23:30:56 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "editor.h"

void	init_editor2(t_doom *doom, t_editor *e)
{
	e->tool_none->background_color = make_rgb(145, 145, 145, 255);
	button_prepare(doom, e->tool_none);
	e->tool_block = create_button(doom, "Block",
		make_rect(10, 195, 60, 60), ed_block_c);
	e->tool_block->background_color = make_rgb(145, 145, 145, 255);
	button_prepare(doom, e->tool_block);
	e->tool_sprite = create_button(doom, "Sprite",
		make_rect(10, 265, 60, 60), ed_sprite_c);
	e->tool_sprite->background_color = make_rgb(145, 145, 145, 255);
	button_prepare(doom, e->tool_sprite);
	e->validate = create_button(doom, "V",
		make_rect(WIN_W - 285, 10, 60, 60), ed_test_map);
	e->validate->background_color = e->select_color;
	e->validate->background_color_disabled = make_rgb(145, 145, 145, 255);
	button_prepare(doom, e->validate);
	e->save = create_button(doom, "Save to file",
		make_rect(WIN_W - 215, 10, 200, 60), ed_save_file);
	e->save->background_color = e->select_color;
	e->save->background_color_disabled = make_rgb(145, 145, 145, 255);
	button_prepare(doom, e->save);
}

void	init_editor3(t_doom *doom, t_editor *e)
{
	if ((e->current_tool =
			create_text(doom, "Current tool : none", FONT_RIFFIC, 30)))
	{
		e->current_tool->ui->pos_x = 90;
		e->current_tool->ui->pos_y = 20;
		text_prepare(doom, e->current_tool, 1, 0);
	}
	if ((e->str_tool = create_text(doom, "Tools", FONT_RIFFIC, 20)))
	{
		e->str_tool->ui->pos_x = 10;
		e->str_tool->ui->pos_y = 90;
		e->str_tool->text_color = make_rgb(0, 0, 0, 255);
		text_prepare(doom, e->str_tool, 1, 0);
	}
	e->rbr_quadrant.orient_hor = create_button(doom, "Hor.",
		make_rect(15, 80, 130, 60), ed_bt_edit_click);
	e->rbr_quadrant.orient_hor->background_color = make_rgb(145, 145, 145, 255);
	add_button_rcoords(e->rbr_quadrant.orient_hor, e->rbr_rect.x,
		e->rbr_rect.y);
	button_prepare(doom, e->rbr_quadrant.orient_hor);
	e->rbr_quadrant.orient_ver = create_button(doom,
		"Vert.", make_rect(155, 80, 130, 60), ed_bt_edit_click);
}

void	init_editor4(t_doom *doom, t_editor *e)
{
	e->rbr_quadrant.orient_ver->background_color = make_rgb(145, 145, 145, 255);
	add_button_rcoords(e->rbr_quadrant.orient_ver,
	e->rbr_rect.x, e->rbr_rect.y);
	button_prepare(doom, e->rbr_quadrant.orient_ver);
	e->rbr_quadrant.texture_n = create_button(doom, "Texture N.",
		make_rect(85, 785, 130, 60), ed_bt_edit_click);
	if (e->rbr_quadrant.texture_n->text)
		e->rbr_quadrant.texture_n->text->text_color =
		make_rgb(255, 255, 255, 255);
	add_button_rcoords(e->rbr_quadrant.texture_n, e->rbr_rect.x, e->rbr_rect.y);
	button_prepare(doom, e->rbr_quadrant.texture_n);
	e->rbr_quadrant.texture_s = create_button(doom, "Texture S.",
		make_rect(85, 925, 130, 60), ed_bt_edit_click);
	if (e->rbr_quadrant.texture_s->text)
		e->rbr_quadrant.texture_s->text->text_color =
		make_rgb(255, 255, 255, 255);
	add_button_rcoords(e->rbr_quadrant.texture_s, e->rbr_rect.x, e->rbr_rect.y);
	button_prepare(doom, e->rbr_quadrant.texture_s);
	e->rbr_quadrant.texture_w = create_button(doom, "Texture W.",
		make_rect(15, 855, 130, 60), ed_bt_edit_click);
	if (e->rbr_quadrant.texture_w->text)
		e->rbr_quadrant.texture_w->text->text_color =
		make_rgb(255, 255, 255, 255);
	add_button_rcoords(e->rbr_quadrant.texture_w, e->rbr_rect.x, e->rbr_rect.y);
	button_prepare(doom, e->rbr_quadrant.texture_w);
}

void	init_editor5(t_doom *doom, t_editor *e)
{
	e->rbr_quadrant.texture_e = create_button(doom, "Texture E.",
	make_rect(155, 855, 130, 60), ed_bt_edit_click);
	if (e->rbr_quadrant.texture_e->text)
		e->rbr_quadrant.texture_e->text->text_color =
		make_rgb(255, 255, 255, 255);
	add_button_rcoords(e->rbr_quadrant.texture_e, e->rbr_rect.x, e->rbr_rect.y);
	button_prepare(doom, e->rbr_quadrant.texture_e);
	e->rbr_quadrant.ev_id = create_wjauge(doom, make_rect(15, 190, 270, 30),
		make_rect(0, 1000, 50, 1));
	e->rbr_quadrant.ev_id->unit = "";
	wjauge_prepare(doom, e->rbr_quadrant.ev_id);
	e->rbr_quadrant.sc_height = create_wjauge(doom, make_rect(15, 265, 270, 30),
		make_rect(0, 1000, 50, 10));
	e->rbr_quadrant.sc_height->unit = "%";
	wjauge_prepare(doom, e->rbr_quadrant.sc_height);
	e->rbr_quadrant.b_w = create_wjauge(doom, make_rect(15, 380, 270, 30),
		make_rect(0, 100, 50, 5));
	e->rbr_quadrant.b_w->unit = "%";
	wjauge_prepare(doom, e->rbr_quadrant.b_w);
	e->rbr_quadrant.b_h = create_wjauge(doom, make_rect(15, 455, 270, 30),
		make_rect(0, 100, 50, 5));
	e->rbr_quadrant.b_h->unit = "%";
	wjauge_prepare(doom, e->rbr_quadrant.b_h);
}

void	init_editor6(t_doom *doom, t_editor *e)
{
	if ((e->state = create_text(doom, "...", FONT_SYS, 18)))
	{
		e->state->ui->pos_x = WIN_W - 500;
		e->state->ui->pos_y = 52;
		e->state->text_color = make_rgb(238, 239, 172, 255);
		text_prepare(doom, e->state, 1, 1);
	}
	e->rbr_quadrant.has_celng =
	create_checkbox(doom, make_rect(256, 310, 29, 29), 0);
	e->rbr_quadrant.sp_collides =
	create_checkbox(doom, make_rect(256, 50, 29, 29), 0);
	e->rbr_quadrant.sp_obtainable =
	create_checkbox(doom, make_rect(256, 90, 29, 29), 0);
	switch_tool(doom, tool_none, NULL);
	doom->average_fps = 0;
	draw_rect_u(e->ed_surface, make_rect(0, 0, WIN_W, WIN_H), 0xFFA1A4A8, 1);
}
