/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:49:20 by lde-batz          #+#    #+#             */
/*   Updated: 2019/03/19 13:41:56 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	ft_init_doom(t_doom *d)
{
	int	fd;

	d->num_sectors = 0;
	if ((fd = open("maps/map-clear.txt", O_RDONLY)) < 0)
		ft_quit(d, "Error: Map no found", 0);
	ft_read_map(fd, d);
	d->player.anglecos = cos(d->player.angle);
	d->player.anglesin = sin(d->player.angle);
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		ft_quit(d, "Initialization SDL", 1);
	d->win = SDL_CreateWindow("Doom-Nukem", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, 0);
//	if ((d->win = SDL_CreateWindow("Doom-Nukem", SDL_WINDOWPOS_CENTERED,
//			SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, 0)) != NULL)
	if (d->win == NULL)
		ft_quit(d, "Impossible to create the window", 1);
	d->rend = SDL_CreateRenderer(d->win, -1, SDL_RENDERER_SOFTWARE);
	if (d->rend == NULL)
		ft_quit(d, "Impossible to create the renderer", 1);
//	if (SDL_CreateWindowAndRenderer(WIN_W, WIN_H, 0, &d->win, &d->rend) != 0)
//		ft_quit(d, "Impossible to create the window and the renderer", 1);
	d->bool_prog = SDL_TRUE;
	d->move.wsad[0] = 0;
	d->move.wsad[1] = 0;
	d->move.wsad[2] = 0;
	d->move.wsad[3] = 0;
	d->move.ground = 0;
	d->move.falling = 1;
	d->move.moving = 0;
	d->move.ducking = 0;
	d->move.yaw = 0.0;
	d->move.speed = 1.0;
}
