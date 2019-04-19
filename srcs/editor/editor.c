/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 02:04:31 by cababou           #+#    #+#             */
/*   Updated: 2019/04/19 05:11:50 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "editor.h"

void	button_callback_test(t_doom *doom, t_el_button *b, SDL_MouseButtonEvent event)
{
	b->rect.x += 25;
	button_prepare(doom, b);
	ft_putendl("ca marche");
}

void	init_editor(t_doom *doom)
{
	if (!(doom->editor = mmalloc(sizeof(t_editor))))
		exit_program(doom, QUIT_MEMERR_AFTER_SDLINIT);

	v2_init_events(doom);

	v2_register_event(doom, SDL_QUIT, quit_event);
	v2_register_event(doom, SDL_KEYUP, key_event);
	v2_register_event(doom, SDL_MOUSEBUTTONUP, button_click);

	doom->surface = SDL_GetWindowSurface(doom->win);

	doom->average_fps = 0;
	doom->fps_counter = create_text(doom, "- fps", FONT_RIFFIC, 20);
	doom->fps_counter->ui_element->pos_x = 8;
	doom->fps_counter->ui_element->pos_y = 8;

	doom->editor->test_button = create_button(doom, "Test Button",
		make_rect(250, 80, 200, 50),
		button_callback_test);
	button_prepare(doom, doom->editor->test_button);
}

void	render_editor(t_doom *doom)
{
	SDL_SetRenderDrawColor(doom->rend, 0xA1, 0xA4, 0xA8, 0xFF );
    SDL_RenderClear(doom->rend);

	draw_rect(doom, make_rect(125, 125, 125, 125), make_rgb(255, 0, 0, 255));

	button_render(doom, doom->editor->test_button);

	doom->fps_counter->text = ft_strjoin(ft_itoa(doom->average_fps), " fps", 1);
	text_prepare(doom, doom->fps_counter, 1);
	text_render(doom, doom->fps_counter);
}

void	loop_editor(t_doom *doom)
{
	Uint32	time;
	t_settings	*sett;

	sett = doom->settings;
	while (1)
	{
		doom->last_frame = SDL_GetTicks();
		while (SDL_PollEvent(&doom->event))
		{
			//printf("Event type : %d\n", doom->event.type);
			v2_distribute_events(doom, doom->event);
		}
		render_editor(doom);
		SDL_UpdateWindowSurface(doom->win);
		time = (SDL_GetTicks() - doom->last_frame);
		SDL_Delay(time > sett->framerate ? 0 : sett->framerate - time);
		time = (SDL_GetTicks() - doom->last_frame);
		doom->average_fps = (1000 / time);
	}
}
