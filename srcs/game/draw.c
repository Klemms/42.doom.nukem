/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 18:15:46 by cababou           #+#    #+#             */
/*   Updated: 2019/04/19 17:20:11 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	init_game(t_doom *doom)
{
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetWindowGrab(doom->win, SDL_TRUE);
	//SDL_SetRelativeMouseMode(SDL_TRUE); -- Comment fix tous les problemes de souris
	// quand on la bouge trop vite, mais ca demande de rework les events de souris,
	// je le ferais peut etre plus tard

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
    ft_print_screen(doom);
	doom->fps_counter->text = ft_strjoin(ft_itoa(doom->average_fps), " fps", 1);
	text_prepare(doom, doom->fps_counter, 1);
	text_render(doom, doom->fps_counter);
	render_hypercam(doom);
    /* Vertical collision detection */
    doom->move.eye_h = (doom->move.ducking) ? DUCK_CAM_H : CAM_H;
    doom->move.ground = !doom->move.falling;
    if (doom->move.falling)
        ft_falling(doom);
    /* Horizontal collision detection */
    if (doom->move.moving)
        ft_moving(doom, &doom->player);
    while (SDL_PollEvent(&doom->event))
        ft_event(doom);
    //ft_move_player(doom, 0, 0);
    ft_move_wsad(doom, &doom->move, &doom->player);
}

void	loop_game(t_doom *doom)
{
	Uint32		time;
	t_settings	*sett;

	sett = doom->settings;
	while (1)
	{
		doom->last_frame = SDL_GetTicks();
		render_game(doom);
		SDL_UpdateWindowSurface(doom->win);
		time = (SDL_GetTicks() - doom->last_frame);
		SDL_Delay(time > sett->framerate ? 0 : sett->framerate - time);
		time = (SDL_GetTicks() - doom->last_frame);
		doom->average_fps = (1000 / time);
	}
}
