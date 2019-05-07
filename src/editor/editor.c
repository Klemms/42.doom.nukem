/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 02:04:31 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 06:17:32 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "editor.h"

void	init_editor_sizes(t_doom *doom)
{
	doom->editor.in_x = 95;
	doom->editor.in_y = 95;
	doom->editor.in_width = WIN_W - 95 - 300 - 15;
	doom->editor.in_height = WIN_H - 95 - 300 - 15;
	doom->editor.sep_size = 15;
	doom->editor.square_width = doom->editor.in_width / 2 - doom->editor.sep_size / 2;
	doom->editor.square_height = doom->editor.in_height / 2 - doom->editor.sep_size / 2;
}

void	init_editor(t_doom *doom)
{
	t_editor	*e;

	e = &doom->editor;
	e->anim_finished = 1;
	e->ed_surface = SDL_CreateRGBSurfaceWithFormat(0, WIN_W, WIN_H, 32, doom->surface->format->format);
	init_editor_sizes(doom);

	e->base_color = make_rgb(145, 145, 145, 255);
	e->select_color = make_rgb(150, 150, 115, 255);
	e->c_focus = -1;
	e->x_focus = -1;
	e->y_focus = -1;

	editor_init_map(doom);

	e->selected_block = NULL;

	register_event(doom, SDL_QUIT, quit_event);
	register_event(doom, SDL_KEYUP, key_event);
	register_event(doom, SDL_MOUSEBUTTONUP, button_click);
	register_event(doom, SDL_MOUSEWHEEL, zoom_event);
	register_event(doom, SDL_MOUSEWHEEL, rbr_wheel);
	register_event(doom, SDL_MOUSEBUTTONDOWN, ed_mouse_button);
	register_event(doom, SDL_MOUSEBUTTONUP, ed_mouse_button);
	register_event(doom, SDL_MOUSEBUTTONUP, rbr_click);
	register_event(doom, SDL_MOUSEMOTION, ed_mouse_motion);

	e->l_textures = list_files("./textures/");

	e->ftr_rect = make_rect(e->in_x, e->in_y, e->in_width, e->in_height);
	e->ftr = SDL_CreateRGBSurfaceWithFormat(0, e->in_width, e->in_height, 32, doom->surface->format->format);
	e->ftr_quadrant.zoom_level = e->ftr_rect.h / doom->nmap->size_y * 0.9;
	e->ftr_quadrant.x_start = e->ftr_rect.w / 2 - doom->nmap->size_x * e->ftr_quadrant.zoom_level / 2;
	e->ftr_quadrant.y_start = e->ftr_rect.h / 2 - doom->nmap->size_y * e->ftr_quadrant.zoom_level / 2;
	e->ftr_quadrant.pos_x = e->ftr_rect.x;
	e->ftr_quadrant.pos_y = e->ftr_rect.y;

	e->bsr_rect = make_rect(0, WIN_H - 300, WIN_W - 300, 300);
	e->bsr = SDL_CreateRGBSurfaceWithFormat(0, e->bsr_rect.w, e->bsr_rect.h, 32, doom->surface->format->format);
	e->bsr_quadrant.pos_x = e->bsr_rect.x;
	e->bsr_quadrant.pos_y = e->bsr_rect.y;

	e->rbr_rect = make_rect(WIN_W - 300, 80, 300, WIN_H - 80);
	e->rbr = SDL_CreateRGBSurfaceWithFormat(0, e->rbr_rect.w, e->rbr_rect.h, 32, doom->surface->format->format);
	e->rbr_quadrant.pos_x = e->rbr_rect.x;
	e->rbr_quadrant.pos_y = e->rbr_rect.y;

	e->tool_none = create_button(doom, "None", make_rect(10, 125, 60, 60), ed_none_c);
	e->tool_none->background_color = make_rgb(145, 145, 145, 255);
	button_prepare(doom, e->tool_none);
	e->tool_block = create_button(doom, "Block", make_rect(10, 195, 60, 60), ed_block_c);
	e->tool_block->background_color = make_rgb(145, 145, 145, 255);
	button_prepare(doom, e->tool_block);

	e->validate = create_button(doom, "V", make_rect(WIN_W - 285, 10, 60, 60), ed_test_map);
	e->validate->background_color = e->select_color;
	e->validate->background_color_disabled = make_rgb(145, 145, 145, 255);
	button_prepare(doom, e->validate);
	e->save = create_button(doom, "Save to file", make_rect(WIN_W - 215, 10, 200, 60), ed_save_file);
	e->save->background_color = e->select_color;
	e->save->background_color_disabled = make_rgb(145, 145, 145, 255);
	button_prepare(doom, e->save);

	e->current_tool = create_text(doom, "Current tool : none", FONT_RIFFIC, 30);
	e->current_tool->ui->pos_x = 90;
	e->current_tool->ui->pos_y = 20;
	text_prepare(doom, e->current_tool, 1, 0);

	e->str_tool = create_text(doom, "Tools", FONT_RIFFIC, 20);
	e->str_tool->ui->pos_x = 10;
	e->str_tool->ui->pos_y = 90;
	e->str_tool->text_color = make_rgb(0, 0, 0, 255);
	text_prepare(doom, e->str_tool, 1, 0);

	e->rbr_quadrant.orient_hor = create_button(doom, "Hor.", make_rect(15, 80, 130, 60), ed_bt_edit_click);
	e->rbr_quadrant.orient_hor->background_color = make_rgb(145, 145, 145, 255);
	add_button_rcoords(e->rbr_quadrant.orient_hor, e->rbr_rect.x, e->rbr_rect.y);
	button_prepare(doom, e->rbr_quadrant.orient_hor);
	e->rbr_quadrant.orient_ver = create_button(doom, "Vert.", make_rect(155, 80, 130, 60), ed_bt_edit_click);
	e->rbr_quadrant.orient_ver->background_color = make_rgb(145, 145, 145, 255);
	add_button_rcoords(e->rbr_quadrant.orient_ver, e->rbr_rect.x, e->rbr_rect.y);
	button_prepare(doom, e->rbr_quadrant.orient_ver);

	e->rbr_quadrant.texture_n = create_button(doom, "Texture N.", make_rect(85, 785, 130, 60), ed_bt_edit_click);
	e->rbr_quadrant.texture_n->text->text_color = make_rgb(255, 255, 255, 255);
	add_button_rcoords(e->rbr_quadrant.texture_n, e->rbr_rect.x, e->rbr_rect.y);
	button_prepare(doom, e->rbr_quadrant.texture_n);
	e->rbr_quadrant.texture_s = create_button(doom, "Texture S.", make_rect(85, 925, 130, 60), ed_bt_edit_click);
	e->rbr_quadrant.texture_s->text->text_color = make_rgb(255, 255, 255, 255);
	add_button_rcoords(e->rbr_quadrant.texture_s, e->rbr_rect.x, e->rbr_rect.y);
	button_prepare(doom, e->rbr_quadrant.texture_s);
	e->rbr_quadrant.texture_w = create_button(doom, "Texture W.", make_rect(15, 855, 130, 60), ed_bt_edit_click);
	e->rbr_quadrant.texture_w->text->text_color = make_rgb(255, 255, 255, 255);
	add_button_rcoords(e->rbr_quadrant.texture_w, e->rbr_rect.x, e->rbr_rect.y);
	button_prepare(doom, e->rbr_quadrant.texture_w);
	e->rbr_quadrant.texture_e = create_button(doom, "Texture E.", make_rect(155, 855, 130, 60), ed_bt_edit_click);
	e->rbr_quadrant.texture_e->text->text_color = make_rgb(255, 255, 255, 255);
	add_button_rcoords(e->rbr_quadrant.texture_e, e->rbr_rect.x, e->rbr_rect.y);
	button_prepare(doom, e->rbr_quadrant.texture_e);

	e->rbr_quadrant.s_height = create_wjauge(doom, make_rect(15, 190, 270, 30), make_rect(0, 1000, 50, 10));
	e->rbr_quadrant.s_height->unit = "%";
	wjauge_prepare(doom, e->rbr_quadrant.s_height);
	e->rbr_quadrant.sc_height = create_wjauge(doom, make_rect(15, 265, 270, 30), make_rect(0, 1000, 50, 10));
	e->rbr_quadrant.sc_height->unit = "%";
	wjauge_prepare(doom, e->rbr_quadrant.sc_height);
	e->rbr_quadrant.b_w = create_wjauge(doom, make_rect(15, 380, 270, 30), make_rect(0, 100, 50, 5));
	e->rbr_quadrant.b_w->unit = "%";
	wjauge_prepare(doom, e->rbr_quadrant.b_w);
	e->rbr_quadrant.b_h = create_wjauge(doom, make_rect(15, 455, 270, 30), make_rect(0, 100, 50, 5));
	e->rbr_quadrant.b_h->unit = "%";
	wjauge_prepare(doom, e->rbr_quadrant.b_h);

	e->state = create_text(doom, "...", FONT_SYS, 18);
	e->state->ui->pos_x = WIN_W - 500;
	e->state->ui->pos_y = 52;
	e->state->text_color = make_rgb(238, 239, 172, 255);
	text_prepare(doom, e->state, 1, 1);

	e->rbr_quadrant.has_celng = create_checkbox(doom, make_rect(256, 310, 29, 29), 0);

	switch_tool(doom, tool_none, NULL);

	doom->average_fps = 0;

	draw_rect_u(e->ed_surface, make_rect(0, 0, WIN_W, WIN_H), 0xFFA1A4A8, 1);
}

void	render_editor(t_doom *doom)
{
	t_editor	*e;
	SDL_Rect	m_pos;

	m_pos = mouse_pos();
	e = &doom->editor;
	SDL_SetRenderDrawColor(doom->rend, 0xA1, 0xA4, 0xA8, 0xFF );
    SDL_RenderClear(doom->rend);

	if (mouse_in(m_pos.x, m_pos.y, doom->editor.ftr_rect))
		doom->editor.c_focus = 1;
	else
		doom->editor.c_focus = -1;

	//draw_rect(e->ed_surface, make_rect(e->in_x, e->in_y, e->square_width, e->square_height), make_rgb(255, 125, 0, 255), 1);
	editor_ftr_brender(doom);
	//draw_rect(e->ed_surface, make_rect(e->in_x, e->in_y + e->square_height + e->sep_size, e->square_width, e->square_height), make_rgb(255, 0, 255, 255), 1);
	//draw_rect(e->ed_surface, make_rect(e->in_x + e->square_width + e->sep_size, e->in_y + e->square_height + e->sep_size, e->square_width, e->square_height), make_rgb(0, 255, 125, 255), 1);
	
	// TOPBAR and SIDEBARS and BOTTOMBAR
	draw_rect_u(e->ed_surface, make_rect(0, 0, WIN_W, 80), 0xFF626468, 1);
	draw_rect_u(e->ed_surface, make_rect(0, 80, 80, WIN_H - 80 - 300), 0xFFd4d5d8, 1);
	//draw_rect(e->ed_surface, make_rect(WIN_W - 300, 80, 300, WIN_H - 80), make_rgb(0, 255, 0, 255), 1);
	editor_rbr_brender(doom);
	editor_bsr_brender(doom);
	//draw_rect(e->ed_surface, make_rect(0, WIN_H - 300, WIN_W - 300, 300), make_rgb(0, 0, 255, 255), 1);

	button_render(doom, e->ed_surface, e->tool_none);
	button_render(doom, e->ed_surface, e->tool_block);
	button_render(doom, e->ed_surface, e->validate);
	button_render(doom, e->ed_surface, e->save);
	text_render(doom, e->ed_surface, e->current_tool);
	text_render(doom, e->ed_surface, e->str_tool);
	draw_rect(e->ed_surface, make_rect(WIN_W - 710, 0, 3, 80), e->base_color, 1);
	draw_rect(e->ed_surface, make_rect(WIN_W - 300, 0, 3, 80), e->base_color, 1);
	doom->tmp_color = make_rgb(255, 255, 255, 255);
	instant_text(doom, e->ed_surface, "Last status :", make_rect(WIN_W - 700, 5, 18, 0));
	text_render(doom, e->ed_surface, e->state);

	free(doom->fps_counter->text);
	doom->fps_counter->text = ft_strjoin(ft_itoa(doom->average_fps), " fps", 1);
	text_prepare(doom, doom->fps_counter, 1, 0);
	text_render(doom, e->ed_surface, doom->fps_counter);
}

void	loop_editor(t_doom *doom)
{
	Uint32	time;
	t_settings	*sett;
	SDL_Rect	mouse;

	sett = &doom->settings;
	while (1)
	{
		doom->last_frame = SDL_GetTicks();
		mouse = mouse_pos();
		doom->m_x = mouse.x;
		doom->m_y = mouse.y;
		if (doom->game_mode == M_EDITOR && doom->editor.anim_finished)
		{
			while (SDL_PollEvent(&doom->last_event))
				distribute_events(doom, doom->last_event);
			render_editor(doom);
			SDL_BlitSurface(doom->editor.ed_surface, NULL, doom->surface, NULL);
		}
		else
		{
			if (doom->game_mode == M_GAME)
				game_loop(doom, sett);
			if (!doom->editor.anim_finished)
			{
				if (doom->game_mode == M_GAME)
					fade_surface(doom);
				else
					fade_surface_back(doom);
				
			}
		}
		SDL_UpdateWindowSurface(doom->win);
		time = (SDL_GetTicks() - doom->last_frame);
		SDL_Delay(time > sett->framerate ? 0 : sett->framerate - time);
		time = (SDL_GetTicks() - doom->last_frame);
		doom->average_fps = (1000 / time);
	}
}
