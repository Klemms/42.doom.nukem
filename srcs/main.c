/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:17:14 by lde-batz          #+#    #+#             */
/*   Updated: 2019/04/12 11:28:35 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

// parkinson dans les coins 90 < angle < 180
// bug plusieurs secteur sur un point 

t_xy	ft_intersect_lines(t_xy p1, t_xy p2, t_xy p3, t_xy p4)
{
	t_xy	d1;
	t_xy	d2;
	t_xy	i;

	if (p2.x - p1.x == 0 || p4.x - p3.x == 0)
	{
		i.x = 0;
		i.y = 0;
		i.next = &d1;
		return (i);
	}
	d1.x = (p2.y - p1.y) / (p2.x - p1.x);
	d2.x = (p4.y - p3.y) / (p4.x - p3.x);
	if (d1.x == d2.x)
	{
		i.x = 0;
		i.y = 0;
		i.next = &d1;
		return (i);
	}
	d1.y = p1.y - (d1.x * p1.x);
	d2.y = p3.y - (d2.x * p3.x);
	i.x = (d2.y - d1.y) / (d1.x - d2.x);
	i.y = d1.x * i.x + d1.y;
	return (i);
}

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
