/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 18:15:46 by cababou           #+#    #+#             */
/*   Updated: 2019/04/30 20:24:54 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void			pixel_put(t_doom *doom, int x, int y, int color)
{
	if (x >= 0 && x < doom->settings.window_width && y >= 0 && y < doom->settings.window_height)
		((Uint32 *)doom->surface->pixels)[y * doom->settings.window_width + x] = color;
}

void	init_game(t_doom *doom)
{
	/*SDL_ShowCursor(SDL_DISABLE);
	SDL_SetWindowGrab(doom->win, SDL_TRUE);*/
	//SDL_SetRelativeMouseMode(SDL_TRUE); -- Comment fix tous les problemes de souris
	// quand on la bouge trop vite, mais ca demande de rework les events de souris,
	// je le ferais peut etre plus tard

	init_events(doom);
	init_textures(doom);
	register_event(doom, SDL_KEYDOWN, key_down);
	register_event(doom, SDL_KEYUP, key_up);
	register_event(doom, SDL_QUIT, quit_window);

	new_player(doom, &doom->you, &doom->map);

	doom->surface = SDL_GetWindowSurface(doom->win);
	
	doom->average_fps = 0;
	doom->fps_counter = create_text(doom, "- fps", FONT_RIFFIC, 20);
	doom->fps_counter->ui_element->pos_x = 8;
	doom->fps_counter->ui_element->pos_y = 8;
	setup_hypercam(doom);
}

void	render_game(t_doom *doom)
{
	SDL_SetRenderDrawColor(doom->rend, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderClear(doom->rend);

	calc_lov(doom);

	doom->fps_counter->text = ft_strjoin(ft_itoa(doom->average_fps), " fps", 1);
	text_prepare(doom, doom->fps_counter, 1);
	text_render(doom, doom->fps_counter);
	render_hypercam(doom);

	
}

void	loop_game(t_doom *doom)
{
	Uint32		time;
	t_settings	*sett;

	sett = &doom->settings;
	while (1)
	{
		doom->last_frame = SDL_GetTicks();
		while (SDL_PollEvent(&doom->last_event))
			distribute_events(doom, doom->last_event);
		render_game(doom);
		
		SDL_UpdateWindowSurface(doom->win);
		time = (SDL_GetTicks() - doom->last_frame);
		SDL_Delay(time > sett->framerate ? 0 : sett->framerate - time);
		time = (SDL_GetTicks() - doom->last_frame);
		doom->you.speed = 0.1;
		doom->you.rotspeed = 0.05;
		doom->average_fps = (1000 / time);
		if (doom->keys.right == 1)
			turn(-doom->you.rotspeed, &doom->you);
		if (doom->keys.left == 1)
			turn(doom->you.rotspeed, &doom->you);
		if (doom->keys.up == 1)
			moove(doom->you.speed, &doom->you, &doom->map, 0);
		if (doom->keys.down == 1)
			moove(-doom->you.speed, &doom->you, &doom->map, 0);
		doom->you.speed = doom->settings.framerate * 5.0;
		doom->you.rotspeed = doom->settings.framerate * 3.0;
	}
}
