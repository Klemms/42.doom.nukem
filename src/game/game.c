/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 18:15:46 by cababou           #+#    #+#             */
/*   Updated: 2019/05/03 02:34:08 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	init_game(t_doom *doom)
{
	SDL_SetRelativeMouseMode(SDL_TRUE);
	doom->mouse_focused = 1;
	doom->game_init = 1;
	
	register_event(doom, SDL_KEYDOWN, key_down);
	register_event(doom, SDL_KEYUP, key_up);
	register_event(doom, SDL_QUIT, quit_window);
	register_event(doom, SDL_MOUSEMOTION, mouse_movement);

	new_player(doom, &doom->you, &doom->map);
	
	doom->average_fps = 0;
	setup_hypercam(doom);
}

void	render_game(t_doom *doom)
{
	SDL_SetRenderDrawColor(doom->rend,
		doom->nmap->skybox_color.r, 
		doom->nmap->skybox_color.g, 
		doom->nmap->skybox_color.b, 0xFF);
    SDL_RenderClear(doom->rend);

	//calc_lov(doom);
	draw_screen(doom);
	doom->fps_counter->text = ft_strjoin(ft_itoa(doom->average_fps), " fps", 1);
	text_prepare(doom, doom->fps_counter, 1);
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

	if (doom->keys.up == 1)
	{
		if (doom->keys.right == 1)
			moove(doom->you.speed, &doom->you, &doom->map, -M_PI_4);
		else if (doom->keys.left == 1)
			moove(doom->you.speed, &doom->you, &doom->map, M_PI_4);
		else
			moove(doom->you.speed, &doom->you, &doom->map, 0);
	}
	else if (doom->keys.down == 1)
	{
		if (doom->keys.right == 1)
			moove(-doom->you.speed, &doom->you, &doom->map, -M_PI_4);
		else if (doom->keys.left == 1)
			moove(-doom->you.speed, &doom->you, &doom->map, M_PI_4);
		else
			moove(-doom->you.speed, &doom->you, &doom->map, 0);
	}
	else if (doom->keys.right == 1)
		moove(doom->you.speed, &doom->you, &doom->map, -M_PI_2);
	else if (doom->keys.left == 1)
		moove(doom->you.speed, &doom->you, &doom->map, M_PI_2);
	
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
