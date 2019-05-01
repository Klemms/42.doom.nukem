/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 02:04:31 by cababou           #+#    #+#             */
/*   Updated: 2019/05/02 01:19:51 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "editor.h"

void	init_editor_sizes(t_doom *doom)
{
	doom->editor.in_x = 95;
	doom->editor.in_y = 95;
	doom->editor.in_width = doom->settings.window_width - 95 - 300 - 15;
	doom->editor.in_height = doom->settings.window_height - 95 - 300 - 15;
	doom->editor.sep_size = 15;
	doom->editor.square_width = doom->editor.in_width / 2 - doom->editor.sep_size / 2;
	doom->editor.square_height = doom->editor.in_height / 2 - doom->editor.sep_size / 2;
}

void	init_editor(t_doom *doom)
{
	t_editor	*e;

	e = &doom->editor;
	e->anim_finished = 1;
	e->ed_surface = SDL_CreateRGBSurfaceWithFormat(0, doom->settings.window_width, doom->settings.window_height, 32, doom->surface->format->format);
	init_editor_sizes(doom);

	editor_init_map(doom);

	register_event(doom, SDL_QUIT, quit_event);
	register_event(doom, SDL_KEYUP, key_event);
	register_event(doom, SDL_MOUSEBUTTONUP, button_click);
	register_event(doom, SDL_MOUSEWHEEL, zoom_event);
	register_event(doom, SDL_MOUSEBUTTONDOWN, ed_mouse_button);
	register_event(doom, SDL_MOUSEBUTTONUP, ed_mouse_button);
	register_event(doom, SDL_MOUSEMOTION, ed_mouse_motion);

	e->flat_top_render_rect = make_rect(e->in_x + e->square_width + e->sep_size, e->in_y, e->square_width, e->square_height);
	e->flat_top_render = SDL_CreateRGBSurfaceWithFormat(0, e->square_width, e->square_height, 32, doom->surface->format->format);
	e->flat_top_quadrant.zoom_level = 16;
	e->flat_top_quadrant.pos_x = e->flat_top_render_rect.x;
	e->flat_top_quadrant.pos_y = e->flat_top_render_rect.y;

	e->tool_none = create_button(doom, "None", make_rect(10, 125, 60, 60), ed_none_c);
	button_prepare(doom, e->tool_none);
	e->tool_block = create_button(doom, "Block", make_rect(10, 195, 60, 60), ed_block_c);
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

	doom->average_fps = 0;

	draw_rect_u(e->ed_surface, make_rect(0, 0, doom->settings.window_width, doom->settings.window_height), 0xFFA1A4A8, 1);
}

void	render_editor(t_doom *doom)
{
	t_editor	*e;

	e = &doom->editor;
	SDL_SetRenderDrawColor(doom->rend, 0xA1, 0xA4, 0xA8, 0xFF );
    SDL_RenderClear(doom->rend);

	draw_rect(e->flat_top_render, make_rect(20, 20, 104, 92), make_rgb(255, 0, 255, 255), 1);

	draw_rect(e->ed_surface, make_rect(e->in_x, e->in_y, e->square_width, e->square_height), make_rgb(255, 125, 0, 255), 1);
	editor_ftr_brender(doom);
	draw_rect(e->ed_surface, make_rect(e->in_x, e->in_y + e->square_height + e->sep_size, e->square_width, e->square_height), make_rgb(255, 0, 255, 255), 1);
	draw_rect(e->ed_surface, make_rect(e->in_x + e->square_width + e->sep_size, e->in_y + e->square_height + e->sep_size, e->square_width, e->square_height), make_rgb(0, 255, 125, 255), 1);
	
	// TOPBAR and SIDEBARS and BOTTOMBAR
	draw_rect_u(e->ed_surface, make_rect(0, 0, doom->settings.window_width, 80), 0xFF626468, 1);
	draw_rect_u(e->ed_surface, make_rect(0, 80, 80, doom->settings.window_height - 80 - 300), 0xFFd4d5d8, 1);
	draw_rect(e->ed_surface, make_rect(doom->settings.window_width - 300, 80, 300, doom->settings.window_height - 80), make_rgb(0, 255, 0, 255), 1);
	draw_rect(e->ed_surface, make_rect(0, doom->settings.window_height - 300, doom->settings.window_width - 300, 300), make_rgb(0, 0, 255, 255), 1);

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

	sett = &doom->settings;
	while (1)
	{
		doom->last_frame = SDL_GetTicks();
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
