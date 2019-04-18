/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:17:14 by lde-batz          #+#    #+#             */
/*   Updated: 2019/04/18 06:05:50 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	init_mode(t_doom *doom, int argc, char **argv)
{
	doom->game_mode = 
		argc == 2 && ft_strcmp(argv[1], "editor") == 0 ? M_EDITOR : M_GAME;
}

int		main(int argc, char **argv)
{
	t_doom	*doom;

	doom = ft_init_doom();
	init_ids(doom);
	init_mode(doom, argc, argv);
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
	exit_program(doom, QUIT_GENERIC);
	return (0);
}
