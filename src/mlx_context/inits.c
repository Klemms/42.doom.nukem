/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 23:44:05 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 19:02:38 by cababou          ###   ########.fr       */
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
	doom->settings.key_sprint = SDL_SCANCODE_LSHIFT;
	doom->settings.key_crouch = SDL_SCANCODE_LCTRL;
	doom->settings.key_button = SDL_SCANCODE_E;
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

void	init_musics(t_doom *doom)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)
	== -1)
		exit_program(doom, ERROR_SDL_AUDIO_INIT);
	Mix_AllocateChannels(10);
	if ((doom->musics.bgm = Mix_LoadMUS("musics/bgm.mp3")) == NULL)
		exit_program(doom, ERROR_INVALID_MUSIC);
	if ((doom->musics.walk = Mix_LoadWAV("musics/marche.wav")) == NULL)
		exit_program(doom, ERROR_INVALID_MUSIC);
	if ((doom->musics.shot = Mix_LoadWAV("musics/tir.wav")) == NULL)
		exit_program(doom, ERROR_INVALID_MUSIC);
	Mix_VolumeMusic(MIX_MAX_VOLUME / 5);
	Mix_VolumeChunk(doom->musics.walk, MIX_MAX_VOLUME / 2);
	Mix_VolumeChunk(doom->musics.shot, MIX_MAX_VOLUME / 2);
	Mix_PlayMusic(doom->musics.bgm, -1);
}

void	init_block_types(t_doom *doom)
{
	doom->block_types = lstcontainer_new();
	lstcontainer_add(doom->block_types
		, make_block_type(doom, "Copy Settings", 0xFF7fc8e2, block_copy));
	lstcontainer_add(doom->block_types
		, make_block_type(doom, "Air", 0xFFFFFEDD, block_air));
	lstcontainer_add(doom->block_types
		, make_block_type(doom, "Wall", 0xFF848484, block_wall));
	lstcontainer_add(doom->block_types
		, make_block_type(doom, "Spawn Point", 0xFFC13CC1, block_spawn));
	lstcontainer_add(doom->block_types
		, make_block_type(doom, "End Point", 0xFFF44262, block_end));
	lstcontainer_add(doom->block_types
		, make_block_type(doom, "Door", 0xFFb7af6f, block_door));
	lstcontainer_add(doom->block_types
		, make_block_type(doom, "Window", 0xFFace5d9, block_window));
	lstcontainer_add(doom->block_types
		, make_block_type(doom, "Button", 0xFF5cf9d7, block_button));
	init_sprite_types(doom);
}

void	init_doom(t_doom *doom)
{
	init_sdl(doom);
	init_ids(doom);
	init_fonts(doom);
	init_events(doom);
	doom->surface = SDL_GetWindowSurface(doom->win);
	doom->s_pixels = doom->surface->pixels;
	doom->fps_counter = create_text(doom, "- fps", FONT_RIFFIC, 20);
	doom->fps_counter->ui->pos_x = 8;
	doom->fps_counter->ui->pos_y = 8;
	init_musics(doom);
}
