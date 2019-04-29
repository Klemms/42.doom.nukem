/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:17:14 by lde-batz          #+#    #+#             */
/*   Updated: 2019/04/29 14:53:36 by cababou          ###   ########.fr       */
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

void	init_base(t_doom *doom, int argc, char **argv)
{
	doom->game_mode = 
		argc == 2 && ft_strcmp(argv[1], "editor") == 0 ? M_EDITOR : M_GAME;
	if (!(doom->buttons = lstcontainer_new()))
		exit_program(doom, QUIT_MEMERR_AFTER_SDLINIT);
}

int		main(int argc, char **argv)
{
	t_doom	*doom;

	if (!(doom = mmalloc(sizeof(t_doom))))
		exit_program(NULL, QUIT_MEMERR_BEFORE_SDLINIT);
	init_base(doom, argc, argv);
	ft_init_doom(doom);
	doom->settings->azerty_mode = 0;
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
	exit_program(doom, QUIT_GENERIC);
	return (0);
}
