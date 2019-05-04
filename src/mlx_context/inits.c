/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 23:44:05 by cababou           #+#    #+#             */
/*   Updated: 2019/05/03 02:34:58 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	setup_settings(t_doom *doom)
{
	doom->settings.framerate = 1000.0f / 60;
	doom->settings.default_wall_color = rgba_to_int(176, 193, 145, 255);
	doom->settings.mouse_sensitivity = 0.007;
	doom->settings.key_forward = SDL_SCANCODE_W;
	doom->settings.key_backward = SDL_SCANCODE_S;
	doom->settings.key_left = SDL_SCANCODE_A;
	doom->settings.key_right = SDL_SCANCODE_D;
	doom->settings.z_up = SDL_SCANCODE_P;
	doom->settings.z_down = SDL_SCANCODE_L;
	doom->settings.key_sprint = SDL_SCANCODE_LSHIFT;
	doom->settings.render_textures = 1;
	doom->settings.enable_crt_floor = 1;
}

void	init_sdl(t_doom *doom)
{
	setup_settings(doom);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		exit_program(doom, ERROR_SDL_INIT);
	doom->win = SDL_CreateWindow("Le Doom", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, 0);
	if (doom->win == NULL)
		exit_program(doom, ERROR_SDL_WINDOW_INIT);
	doom->rend = SDL_CreateRenderer(doom->win, -1, SDL_RENDERER_SOFTWARE);
	if (doom->rend == NULL)
		exit_program(doom, ERROR_SDL_RENDERER_INIT);
}

void	init_scores(t_doom *doom)
{
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
		exit_program(doom, ERROR_SDL_AUDIO_INIT);
	Mix_AllocateChannels(10);
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	if ((doom->scores.bgm = Mix_LoadMUS("musics/test.mp3")) == NULL)
		exit_program(doom, ERROR_INVALID_MUSIC);
	if ((doom->scores.walk = Mix_LoadWAV("musics/marche.wav")) == NULL)
		exit_program(doom, ERROR_INVALID_MUSIC);
	if ((doom->scores.shot = Mix_LoadWAV("musics/test_tir.wav")) == NULL)
		exit_program(doom, ERROR_INVALID_MUSIC);
	Mix_PlayMusic(doom->scores.bgm, -1);
	Mix_VolumeChunk(doom->scores.walk, MIX_MAX_VOLUME / 2);
	Mix_VolumeChunk(doom->scores.shot, MIX_MAX_VOLUME / 2);
}

