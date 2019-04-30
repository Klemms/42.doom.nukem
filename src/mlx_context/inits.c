/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 23:44:05 by cababou           #+#    #+#             */
/*   Updated: 2019/04/29 21:21:05 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_doom(t_doom *doom)
{
	if (!(doom->keys = mmalloc(sizeof(t_key)))
		|| !(doom->map = mmalloc(sizeof(t_map)))
		|| !(doom->textures = lstcontainer_new())
		|| !(doom->sight = mmalloc(sizeof(t_sight))))
		exit_program(NULL, ERROR_MEMORY);
}

void	setup_settings(t_doom *doom)
{
	if (!(doom->settings = mmalloc(sizeof(t_settings))))
		exit_program(doom, ERROR_SDL_BEFORE_INIT);
	doom->settings->window_width = doom->game_mode == M_GAME ? 1920 : 2304;
	doom->settings->window_height = doom->game_mode == M_GAME ? 1080 : 1296;
	doom->settings->framerate = 1000.0f / 60;
	doom->settings->angle_h = 0.73f * doom->settings->window_height;
	doom->settings->angle_v = 0.2f * doom->settings->window_height;
}

void	init_sdl(t_doom *doom)
{
	setup_settings(doom);
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		exit_program(doom, ERROR_SDL_INIT);
	doom->win = SDL_CreateWindow("Le Doom", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, doom->settings->window_width, doom->settings->window_height, 0);
	if (doom->win == NULL)
		exit_program(doom, ERROR_SDL_WINDOW_INIT);
	doom->rend = SDL_CreateRenderer(doom->win, -1, SDL_RENDERER_SOFTWARE);
	if (doom->rend == NULL)
		exit_program(doom, ERROR_SDL_RENDERER_INIT);
}
