/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 13:20:21 by hdussert          #+#    #+#             */
/*   Updated: 2019/05/04 18:32:20 by lde-batz         ###   ########.fr       */
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

int		main(int argc, char *argv[])
{
	t_doom doom;

	ft_bzero(&doom, sizeof(t_doom));
	if (argc == 1)
		exit_program(&doom, ERROR_USAGE);
	init_block_types(&doom);
	init_base(&doom, argc, argv);
	if (!parsing(&doom, doom.game_mode == M_EDITOR ? argv[2] : argv[1]))
		exit_program(&doom, ERROR_INVALID_MAP);
	init_doom(&doom);
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
