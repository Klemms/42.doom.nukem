/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:17:14 by lde-batz          #+#    #+#             */
/*   Updated: 2019/03/22 06:12:32 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int		main(int argc, char **argv)
{
	t_doom	*doom;

	doom = ft_init_doom();
	doom->game_mode = 
		argc == 2 && ft_strcmp(argv[1], "editor") == 0 ? M_EDITOR : M_GAME;
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetWindowGrab(doom->win, SDL_TRUE);
	//SDL_SetRelativeMouseMode(SDL_TRUE); -- Comment fix tous les problemes de souris
	// quand on la bouge trop vite, mais ca demande de rework les events de souris,
	// je le ferais peut etre plus tard
	while (doom->bool_prog)
	{
		if (doom->game_mode == M_EDITOR)
		{
			//render_editor(&doom);
		}
		else if (doom->game_mode == M_GAME)
		{
			render_game(doom);
		}
	}
	exit_program(doom, QUIT_GENERIC);
	return (0);
}
