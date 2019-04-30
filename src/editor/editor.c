/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 02:04:31 by cababou           #+#    #+#             */
/*   Updated: 2019/05/01 00:33:36 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "editor.h"

void	button_callback_test(t_doom *d, t_el_button *b, SDL_MouseButtonEvent e)
{
	b->rect.x += 25;
	button_prepare(d, b);
	ft_putendl("ca marche");
}

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
	init_editor_sizes(doom);

	init_events(doom);

	register_event(doom, SDL_QUIT, quit_event);
	register_event(doom, SDL_KEYUP, key_event);
	register_event(doom, SDL_MOUSEBUTTONUP, button_click);

	doom->surface = SDL_GetWindowSurface(doom->win);

	doom->average_fps = 0;
	doom->fps_counter = create_text(doom, "- fps", FONT_RIFFIC, 20);
	doom->fps_counter->ui_element->pos_x = 8;
	doom->fps_counter->ui_element->pos_y = 8;

	doom->editor.test_button = create_button(doom, "Test Button",
		make_rect(250, 80, 200, 50),
		button_callback_test);
	button_prepare(doom, doom->editor.test_button);
}

void	render_editor(t_doom *doom)
{
	t_editor	*e;

	e = &doom->editor;
	SDL_SetRenderDrawColor(doom->rend, 0xA1, 0xA4, 0xA8, 0xFF );
    SDL_RenderClear(doom->rend);

	//draw_rect(doom, make_rect(95, 95, doom->settings->window_width - 95 - 300 - 15, doom->settings->window_height - 95 - 300 - 15), make_rgb(255, 125, 0, 255));
	draw_rect(doom, make_rect(e->in_x, e->in_y, e->square_width, e->square_height), make_rgb(255, 125, 0, 255), 1);
	draw_rect(doom, make_rect(e->in_x + e->square_width + e->sep_size, e->in_y, e->square_width, e->square_height), make_rgb(255, 125, 125, 255), 1);
	draw_rect(doom, make_rect(e->in_x, e->in_y + e->square_height + e->sep_size, e->square_width, e->square_height), make_rgb(255, 0, 255, 255), 1);
	draw_rect(doom, make_rect(e->in_x + e->square_width + e->sep_size, e->in_y + e->square_height + e->sep_size, e->square_width, e->square_height), make_rgb(0, 255, 125, 255), 1);
	/*draw_rect(doom, make_rect(125, 125, 125, 125), make_rgb(255, 0, 0, 255));
	draw_rect(doom, make_rect(125, 125, 125, 125), make_rgb(255, 0, 0, 255));*/

	// TOPBAR and SIDEBARS and BOTTOMBAR
	draw_rect(doom, make_rect(0, 0, doom->settings.window_width, 80), make_rgb(255, 0, 0, 255), 1);
	draw_rect(doom, make_rect(0, 80, 80, doom->settings.window_height - 80 - 300), make_rgb(0, 255, 0, 255), 1);
	draw_rect(doom, make_rect(doom->settings.window_width - 300, 80, 300, doom->settings.window_height - 80), make_rgb(0, 255, 0, 255), 1);
	draw_rect(doom, make_rect(0, doom->settings.window_height - 300, doom->settings.window_width - 300, 300), make_rgb(0, 0, 255, 255), 1);

	button_render(doom, doom->editor.test_button);

	doom->fps_counter->text = ft_strjoin(ft_itoa(doom->average_fps), " fps", 1);
	text_prepare(doom, doom->fps_counter, 1);
	text_render(doom, doom->fps_counter);
}

void	loop_editor(t_doom *doom)
{
	Uint32	time;
	t_settings	*sett;

	sett = &doom->settings;
	while (1)
	{
		doom->last_frame = SDL_GetTicks();
		while (SDL_PollEvent(&doom->last_event))
			distribute_events(doom, doom->last_event);
		render_editor(doom);
		SDL_UpdateWindowSurface(doom->win);
		time = (SDL_GetTicks() - doom->last_frame);
		SDL_Delay(time > sett->framerate ? 0 : sett->framerate - time);
		time = (SDL_GetTicks() - doom->last_frame);
		doom->average_fps = (1000 / time);
	}
}
