/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 02:04:31 by cababou           #+#    #+#             */
/*   Updated: 2019/04/18 03:12:45 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

int		quit_event(t_doom *doom, SDL_Event sdl_event)
{
	exit_program(doom, QUIT_GENERIC);

	return (0);
}

int		key_event(t_doom *doom, SDL_Event sdl_event)
{
	if (sdl_event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		exit_program(doom, QUIT_GENERIC);

	return (0);
}

void	init_editor(t_doom *doom)
{
	editor_init_events(doom);

	editor_register_event(doom, SDL_QUIT, quit_event);
	editor_register_event(doom, SDL_KEYUP, key_event);

	doom->surface = SDL_GetWindowSurface(doom->win);
}

void	render_editor(t_doom *doom)
{
	SDL_SetRenderDrawColor(doom->rend, 0xA1, 0xA4, 0xA8, 0xFF );
    SDL_RenderClear(doom->rend);

	SDL_Rect fillRect = { 125, 125, 125, 125 };
	SDL_SetRenderDrawColor(doom->rend, 0xFF, 0x00, 0x00, 0xFF );
	SDL_RenderFillRect(doom->rend, &fillRect );
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
			printf("Event type : %d\n", doom->event.type);
			editor_distribute_events(doom, doom->event);
		}
		render_editor(doom);
		SDL_UpdateWindowSurface(doom->win);
		time = (SDL_GetTicks() - doom->last_frame);
		SDL_Delay(time > sett->framerate ? 0 : sett->framerate - time);
	}
}
