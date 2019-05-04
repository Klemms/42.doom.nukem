/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 13:20:21 by hdussert          #+#    #+#             */
/*   Updated: 2019/05/04 09:09:24 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_base(t_doom *doom, int argc, char **argv)
{
	doom->game_mode = 
		argc >= 2 && ft_strcmp(argv[1], "editor") == 0 ? M_EDITOR : M_GAME;
	doom->original_mode = doom->game_mode;
	if (doom->game_mode == M_EDITOR && argc < 3)
		exit_program(doom, ERROR_EDITOR_NEED_MAP);
	if (!(doom->buttons = lstcontainer_new()))
		exit_program(doom, ERROR_SDL_AFTER_INIT);
}

int			main(int argc, char *argv[])
{
	t_doom doom;

	ft_bzero(&doom, sizeof(t_doom));
	if (argc == 1)
		exit_program(&doom, ERROR_USAGE);
	doom.textures = lstcontainer_new();
	init_base(&doom, argc, argv);
	if (!parsing(&doom, doom.game_mode == M_EDITOR ? argv[2] : argv[1]))
		exit_program(&doom, ERROR_INVALID_MAP);
	init_sdl(&doom);
	init_ids(&doom);
	init_fonts(&doom);
	init_events(&doom);
	doom.surface = SDL_GetWindowSurface(doom.win);
	doom.s_pixels = doom.surface->pixels;
	doom.fps_counter = create_text(&doom, "- fps", FONT_RIFFIC, 20);
	doom.fps_counter->ui->pos_x = 8;
	doom.fps_counter->ui->pos_y = 8;
	init_textures(&doom);
	init_scores(&doom);
	doom.nmap = convert_map(&doom, &doom.old_map, doom.textures);
	if (doom.game_mode == M_GAME)
	{
		init_game(&doom);
		loop_game(&doom);
	}
	else if (doom.game_mode == M_EDITOR)
	{
		init_editor(&doom);
		loop_editor(&doom);
	}
	exit_program(&doom, ERROR_GENERIC);
	return (0);
}
