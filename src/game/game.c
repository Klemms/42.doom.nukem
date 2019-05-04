/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 18:15:46 by cababou           #+#    #+#             */
/*   Updated: 2019/05/04 10:50:22 by cababou          ###   ########.fr       */
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

	new_player(doom, &doom->you, doom->nmap);
	
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
	free(doom->fps_counter->text);
	doom->fps_counter->text = ft_strjoin(ft_itoa(doom->average_fps), " fps", 1);
	text_prepare(doom, doom->fps_counter, 1, 0);
	text_render(doom, doom->surface, doom->fps_counter);
	render_hypercam(doom, doom->surface);


	t_quadrant_renderer	*q;
	int					x;
	int					y;
	SDL_Rect			r;

	q = &doom->editor.ftr_quadrant;
	y = 0;
	while (y < doom->nmap->size_y)
	{
		x = 0;
		while (x < doom->nmap->size_x)
		{
			r = make_rect(100 + x * 15, 100 + y * 15, 15, 15);
			draw_rect_u(doom->surface, r, block_type(doom, doom->nmap->map[y][x].block_type)->block_color, 1);
			/*if (mouse_in(m_pos.x - q->pos_x, m_pos.y - q->pos_y, r))
			{
				//draw_rect_u(doom->editor.ftr, r, 0xFF000000, 0);
			}*/
			x++;
		}
		y++;
	}	
	draw_rect_u(doom->surface, make_rect(100 + doom->you.pos.x * 15, 100 + doom->you.pos.y * 15, 5, 5), 0xFFFF0000, 1);
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

	/*if (doom->keys.up == 1)
	{
		if (doom->keys.right == 1)
			moove(doom->you.speed, &doom->you, doom->nmap, -M_PI_4);
		else if (doom->keys.left == 1)
			moove(doom->you.speed, &doom->you, doom->nmap, M_PI_4);
		else
			moove(doom->you.speed, &doom->you, doom->nmap, 0);
	}
	else if (doom->keys.down == 1)
	{
		if (doom->keys.right == 1)
			moove(-doom->you.speed, &doom->you, doom->nmap, -M_PI_4);
		else if (doom->keys.left == 1)
			moove(-doom->you.speed, &doom->you, doom->nmap, M_PI_4);
		else
			moove(-doom->you.speed, &doom->you, &doom->nmap, 0);
	}
	else if (doom->keys.right == 1)
		moove(doom->you.speed, &doom->you, doom->nmap, -M_PI_2);
	else if (doom->keys.left == 1)
		moove(doom->you.speed, &doom->you, doom->nmap, M_PI_2);*/
	
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
