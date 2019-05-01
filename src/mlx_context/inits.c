/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 23:44:05 by cababou           #+#    #+#             */
/*   Updated: 2019/05/01 21:27:46 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	setup_settings(t_doom *doom)
{
	doom->settings.window_width = doom->game_mode == M_GAME ? 1920 : 2304;
	doom->settings.window_height = doom->game_mode == M_GAME ? 1080 : 1296;
	doom->w = doom->settings.window_width;
	doom->h = doom->settings.window_height;
	doom->settings.framerate = 1000.0f / 60;
	doom->settings.angle_h = 0.73f * doom->settings.window_height;
	doom->settings.angle_v = 0.2f * doom->settings.window_height;
	doom->settings.default_wall_color = rgba_to_int(176, 193, 145, 255);
	doom->settings.mouse_sensitivity = 0.007;
	doom->settings.key_forward = SDL_SCANCODE_W;
	doom->settings.key_backward = SDL_SCANCODE_S;
	doom->settings.key_left = SDL_SCANCODE_A;
	doom->settings.key_right = SDL_SCANCODE_D;
	doom->settings.key_sprint = SDL_SCANCODE_LSHIFT;
	doom->settings.render_textures = 1;
}

void	init_sdl(t_doom *doom)
{
	setup_settings(doom);
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		exit_program(doom, ERROR_SDL_INIT);
	doom->win = SDL_CreateWindow("Le Doom", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, doom->settings.window_width, doom->settings.window_height, 0);
	if (doom->win == NULL)
		exit_program(doom, ERROR_SDL_WINDOW_INIT);
	doom->rend = SDL_CreateRenderer(doom->win, -1, SDL_RENDERER_SOFTWARE);
	if (doom->rend == NULL)
		exit_program(doom, ERROR_SDL_RENDERER_INIT);
}
