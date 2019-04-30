/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 13:20:21 by hdussert          #+#    #+#             */
/*   Updated: 2019/04/29 21:30:47 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_base(t_doom *doom, int argc, char **argv)
{
	doom->game_mode = 
		argc == 2 && ft_strcmp(argv[1], "editor") == 0 ? M_EDITOR : M_GAME;
	if (!(doom->buttons = lstcontainer_new()))
		exit_program(doom, ERROR_SDL_AFTER_INIT);
}

int			main(int argc, char *argv[])
{

	if (!(doom = mmalloc(sizeof(t_doom))))
		exit_program(NULL, ERROR_MEMORY);
	init_base(doom, argc, argv);
	init_doom(doom);
	if (!parsing(doom, argv[1]))
		exit_program(doom, ERROR_INVALID_MAP);
	init_sdl(doom);
	init_ids(doom);
	init_fonts(doom);
	if (doom->game_mode == M_GAME)
	{
		init_game(doom);
		loop_game(doom);
	}
	else if (doom->game_mode == M_EDITOR)
	{
		init_editor(doom);
		loop_editor(doom);
	}
	exit_program(doom, ERROR_GENERIC);
	return (0);
}

	t_doom	*doom;