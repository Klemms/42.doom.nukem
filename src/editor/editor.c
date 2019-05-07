/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 02:04:31 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 23:51:02 by bsiche           ###   ########.fr       */
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
	doom->editor.square_width = doom->editor.in_width
	/ 2 - doom->editor.sep_size / 2;
	doom->editor.square_height = doom->editor.in_height
	/ 2 - doom->editor.sep_size / 2;
}

void	rendet_edit_button(t_doom *doom, t_editor *e)
{
	button_render(doom, e->ed_surface, e->tool_none);
	button_render(doom, e->ed_surface, e->tool_block);
	button_render(doom, e->ed_surface, e->tool_sprite);
	button_render(doom, e->ed_surface, e->validate);
	button_render(doom, e->ed_surface, e->save);
	text_render(doom, e->ed_surface, e->current_tool);
	text_render(doom, e->ed_surface, e->str_tool);
	draw_rect(e->ed_surface,
		make_rect(WIN_W - 710, 0, 3, 80), e->base_color, 1);
	draw_rect(e->ed_surface,
		make_rect(WIN_W - 300, 0, 3, 80), e->base_color, 1);
	doom->tmp_color = make_rgb(255, 255, 255, 255);
	instant_text(doom, e->ed_surface,
		"Last status :", make_rect(WIN_W - 700, 5, 18, 0));
	text_render(doom, e->ed_surface, e->state);
	if (doom->fps_counter)
	{
		free(doom->fps_counter->text);
		doom->fps_counter->text =
		ft_strjoin(ft_itoa(doom->average_fps), " fps", 1);
		text_prepare(doom, doom->fps_counter, 1, 0);
		text_render(doom, e->ed_surface, doom->fps_counter);
	}
}

void	render_editor(t_doom *doom)
{
	t_editor	*e;
	SDL_Rect	m_pos;

	m_pos = mouse_pos();
	e = &doom->editor;
	SDL_SetRenderDrawColor(doom->rend, 0xA1, 0xA4, 0xA8, 0xFF);
	SDL_RenderClear(doom->rend);
	if (mouse_in(m_pos.x, m_pos.y, doom->editor.ftr_rect))
		doom->editor.c_focus = 1;
	else
		doom->editor.c_focus = -1;
	editor_ftr_brender(doom);
	draw_rect_u(e->ed_surface, make_rect(0, 0, WIN_W, 80), 0xFF626468, 1);
	draw_rect_u(e->ed_surface,
		make_rect(0, 80, 80, WIN_H - 80 - 300), 0xFFd4d5d8, 1);
	editor_rbr_brender(doom);
	editor_bsr_brender(doom);
	rendet_edit_button(doom, e);
}

void	game_loop_ed(t_doom *doom, t_settings *sett)
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

void	loop_editor(t_doom *doom)
{
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
			game_loop_ed(doom, sett);
		sdl_edit_update(doom, sett);
	}
}
