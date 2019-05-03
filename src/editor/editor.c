/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 02:04:31 by cababou           #+#    #+#             */
/*   Updated: 2019/05/03 03:30:51 by cababou          ###   ########.fr       */
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

	e->block_types = lstcontainer_new();
	lstcontainer_add(e->block_types, make_block_type(doom, "Air", 0xFFFFFEDD, block_air));
	lstcontainer_add(e->block_types, make_block_type(doom, "Wall", 0xFF848484, block_wall));
	lstcontainer_add(e->block_types, make_block_type(doom, "Small Wall", 0xFFb78c73, block_small_wall));
	lstcontainer_add(e->block_types, make_block_type(doom, "Spawn Point", 0xFFC13CC1, block_spawn));
	e->selected_block = NULL;

	register_event(doom, SDL_QUIT, quit_event);
	register_event(doom, SDL_KEYUP, key_event);
	register_event(doom, SDL_MOUSEBUTTONUP, button_click);
	register_event(doom, SDL_MOUSEWHEEL, zoom_event);
	register_event(doom, SDL_MOUSEBUTTONDOWN, ed_mouse_button);
	register_event(doom, SDL_MOUSEBUTTONUP, ed_mouse_button);
	register_event(doom, SDL_MOUSEMOTION, ed_mouse_motion);

	e->flat_top_render_rect = make_rect(e->in_x, e->in_y, e->in_width, e->in_height);
	e->flat_top_render = SDL_CreateRGBSurfaceWithFormat(0, e->in_width, e->in_height, 32, doom->surface->format->format);
	e->flat_top_quadrant.zoom_level = e->flat_top_render_rect.h / doom->nmap->size_y * 0.9;
	e->flat_top_quadrant.x_start = e->flat_top_render_rect.w / 2 - doom->nmap->size_x * e->flat_top_quadrant.zoom_level / 2;
	e->flat_top_quadrant.y_start = e->flat_top_render_rect.h / 2 - doom->nmap->size_y * e->flat_top_quadrant.zoom_level / 2;
	e->flat_top_quadrant.pos_x = e->flat_top_render_rect.x;
	e->flat_top_quadrant.pos_y = e->flat_top_render_rect.y;

	e->bottom_select_render_rect = make_rect(0, WIN_H - 300, WIN_W - 300, 300);
	e->bottom_select_render = SDL_CreateRGBSurfaceWithFormat(0, e->bottom_select_render_rect.w, e->bottom_select_render_rect.h, 32, doom->surface->format->format);
	e->bottom_select_quadrant.pos_x = e->bottom_select_render_rect.x;
	e->bottom_select_quadrant.pos_y = e->bottom_select_render_rect.y;

	e->right_bar_render_rect = make_rect(WIN_W - 300, 80, 300, WIN_H - 80);
	e->right_bar_render = SDL_CreateRGBSurfaceWithFormat(0, e->right_bar_render_rect.w, e->right_bar_render_rect.h, 32, doom->surface->format->format);
	e->right_bar_quadrant.pos_x = e->right_bar_render_rect.x;
	e->right_bar_quadrant.pos_y = e->right_bar_render_rect.y;

	e->tool_none = create_button(doom, "None", make_rect(10, 125, 60, 60), ed_none_c);
	e->tool_none->background_color = make_rgb(145, 145, 145, 255);
	button_prepare(doom, e->tool_none);
	e->tool_block = create_button(doom, "Block", make_rect(10, 195, 60, 60), ed_block_c);
	e->tool_block->background_color = make_rgb(145, 145, 145, 255);
	button_prepare(doom, e->tool_block);

	e->current_tool = create_text(doom, "Current tool : none", FONT_RIFFIC, 30);
	e->current_tool->ui_element->pos_x = 90;
	e->current_tool->ui_element->pos_y = 20;
	text_prepare(doom, e->current_tool, 1);

	e->str_tool = create_text(doom, "Tools", FONT_RIFFIC, 20);
	e->str_tool->ui_element->pos_x = 10;
	e->str_tool->ui_element->pos_y = 90;
	e->str_tool->text_color = make_rgb(0, 0, 0, 255);
	text_prepare(doom, e->str_tool, 1);

	e->right_bar_quadrant.orient_n = create_button(doom, "N", make_rect(15, 45, 60, 60), ed_bt_edit_click);
	e->right_bar_quadrant.orient_n->background_color = make_rgb(145, 145, 145, 255);
	button_prepare(doom, e->right_bar_quadrant.orient_n);
	e->right_bar_quadrant.orient_s = create_button(doom, "S", make_rect(85, 45, 60, 60), ed_bt_edit_click);
	e->right_bar_quadrant.orient_s->background_color = make_rgb(145, 145, 145, 255);
	button_prepare(doom, e->right_bar_quadrant.orient_s);
	e->right_bar_quadrant.orient_w = create_button(doom, "W", make_rect(155, 45, 60, 60), ed_bt_edit_click);
	e->right_bar_quadrant.orient_w->background_color = make_rgb(145, 145, 145, 255);
	button_prepare(doom, e->right_bar_quadrant.orient_w);
	e->right_bar_quadrant.orient_e = create_button(doom, "E", make_rect(225, 45, 60, 60), ed_bt_edit_click);
	e->right_bar_quadrant.orient_e->background_color = make_rgb(145, 145, 145, 255);
	button_prepare(doom, e->right_bar_quadrant.orient_e);

	switch_tool(doom, tool_none);

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

	if (mouse_in(m_pos.x, m_pos.y, doom->editor.flat_top_render_rect))
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
	text_render(doom, e->ed_surface, e->current_tool);
	text_render(doom, e->ed_surface, e->str_tool);

	doom->fps_counter->text = ft_strjoin(ft_itoa(doom->average_fps), " fps", 1);
	text_prepare(doom, doom->fps_counter, 1);
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
