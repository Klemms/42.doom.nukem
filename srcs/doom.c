/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:49:20 by lde-batz          #+#    #+#             */
/*   Updated: 2019/04/22 05:00:01 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	setup_settings(t_doom *doom)
{
	if (!(doom->settings = mmalloc(sizeof(t_settings))))
		exit_program(doom, QUIT_MEMERR_BEFORE_SDLINIT);
	doom->settings->window_width = 1920;
	doom->settings->window_height = 1080;
	doom->settings->framerate = 1000.0f / 60;
	doom->settings->angle_h = 0.73f * doom->settings->window_height;
	doom->settings->angle_v = 0.2f * doom->settings->window_height;
}

t_doom	*ft_init_doom()
{
	t_doom	*doom;
	int		fd;

	if (!(doom = malloc(sizeof(t_doom))))
		exit_program(NULL, QUIT_MEMERR_BEFORE_SDLINIT);
	ft_bzero(doom, sizeof(t_doom));
	setup_settings(doom);
	doom->num_sectors = 0;
	if ((fd = open("maps/map-clear.txt", O_RDONLY)) < 0)
		exit_program(doom, QUIT_CANT_FIND_MAP);
	ft_read_map(fd, doom);
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		exit_program(doom, QUIT_CANT_INIT_SDL);
	doom->win = SDL_CreateWindow("Doom-Nukem", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, doom->settings->window_width, doom->settings->window_height, 0);
//	if ((d->win = SDL_CreateWindow("Doom-Nukem", SDL_WINDOWPOS_CENTERED,
//			SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, 0)) != NULL)
	if (doom->win == NULL)
		exit_program(doom, QUIT_CANT_INIT_WINDOW);
	doom->rend = SDL_CreateRenderer(doom->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (doom->rend == NULL)
		exit_program(doom, QUIT_CANT_INIT_RENDERER);
//	if (SDL_CreateWindowAndRenderer(WIN_W, WIN_H, 0, &d->win, &d->rend) != 0)
//		ft_quit(d, "Impossible to create the window and the renderer", 1);
	doom->move.wsad[0] = 0;
	doom->move.wsad[1] = 0;
	doom->move.wsad[2] = 0;
	doom->move.wsad[3] = 0;
	doom->move.ground = 0;
	doom->move.falling = 1;
	doom->move.moving = 0;
	doom->move.ducking = 0;
	doom->move.yaw = 0.0;
	doom->move.speed = 1.0;
	return (doom);
}
