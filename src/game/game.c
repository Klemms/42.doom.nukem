/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 18:15:46 by cababou           #+#    #+#             */
/*   Updated: 2019/05/06 11:12:01 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	init_game(t_doom *doom)
{

	//t_sprite  sprites[] = 
  doom->lsprite.sprites = malloc(sizeof(t_sprite) * 4);
	doom->lsprite.sprites[0] = (t_sprite){ { 3,3 }, 0, 2, 1, 0.0 };
	doom->lsprite.sprites[1] = (t_sprite){ { 4.3, 5.5 }, 1, 0, 0, 0.0 };
	doom->lsprite.sprites[2] = (t_sprite){ { 6, 6 }, 1, 1, 1, 0.0 };
	doom->lsprite.sprites[3] = (t_sprite){ { 9.4, 7 }, 2, 0, 0, 0.0 };
	SDL_SetRelativeMouseMode(SDL_TRUE);
	doom->mouse_focused = 1;
	doom->game_init = 1;
	
	register_event(doom, SDL_KEYDOWN, key_down);
	register_event(doom, SDL_KEYUP, key_up);
	register_event(doom, SDL_QUIT, quit_window);
	register_event(doom, SDL_MOUSEMOTION, mouse_movement);
	register_event(doom, SDL_MOUSEBUTTONDOWN, mouse_down);
	register_event(doom, SDL_MOUSEBUTTONUP, mouse_up);

	new_player(doom, &doom->you, doom->nmap);
	
	doom->average_fps = 0;
	setup_hypercam(doom);
}

void	render_game(t_doom *doom)
{
	SDL_SetRenderDrawColor(doom->rend,
		0, 
		0, 
		0, 0xFF);
    SDL_RenderClear(doom->rend);

	//calc_lov(doom);
	draw_screen(doom);
	//draw_minimap(doom);
	free(doom->fps_counter->text);
	doom->fps_counter->text = ft_strjoin(ft_itoa(doom->average_fps), " fps", 1);
	text_prepare(doom, doom->fps_counter, 1, 0);
	text_render(doom, doom->surface, doom->fps_counter);
	render_hypercam(doom, doom->surface);
}

void	game_loop(t_doom *doom, t_settings *sett)
{
	while (SDL_PollEvent(&doom->last_event))
		distribute_events(doom, doom->last_event);
	render_game(doom);
	if (!doom->mouse_focused)
		draw_rect(doom->surface, make_rect(0, 0, WIN_W, WIN_H), make_rgb(255, 0, 0, 255), 0);
	doom->you.speed = doom->you.is_sprinting ? 0.2 : 0.1;
	update_velocity(doom, &doom->you);
	moving(doom);
	
	if (doom->keys.z_up)
		doom->you.pos.z += 0.02;
	else if (doom->keys.z_down)
		doom->you.pos.z -= 0.02;
	
}

void	loop_game(t_doom *doom)
{
	Uint32		time;
	t_settings	*sett;
	SDL_Rect	mouse;

	sett = &doom->settings;
	while (1)
	{
		doom->last_frame = SDL_GetTicks();
		mouse = mouse_pos();
		doom->m_x = mouse.x;
		doom->m_y = mouse.y;
		game_loop(doom, sett);
		SDL_UpdateWindowSurface(doom->win);
		time = (SDL_GetTicks() - doom->last_frame);
		SDL_Delay(time > sett->framerate ? 0 : sett->framerate - time);
		time = (SDL_GetTicks() - doom->last_frame);
		doom->average_fps = (1000 / time);
	}
}
