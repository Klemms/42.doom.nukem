/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 18:15:46 by cababou           #+#    #+#             */
/*   Updated: 2019/03/26 11:20:56 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	render_game(t_doom *doom)
{
	int		frame_limit;

	SDL_RenderClear(doom->rend);
	doom->surface = SDL_GetWindowSurface(doom->win);
	ft_print_screen(doom);
	SDL_UpdateWindowSurface(doom->win);
	frame_limit = SDL_GetTicks() + FPS_LIMIT;
	ft_limit_fps(frame_limit);
	frame_limit = SDL_GetTicks() + FPS_LIMIT;
	/* Vertical collision detection */
	doom->move.eye_h = (doom->move.ducking) ? DUCK_CAM_H : CAM_H;
	doom->move.ground = !doom->move.falling;
	if (doom->move.falling)
		ft_falling(doom);
	/* Horizontal collision detection */
	if (doom->move.moving)
		ft_moving(doom, &doom->player);
	while (SDL_PollEvent(&doom->event))
		ft_event(doom);
	doom->player.anglesin = sin(doom->player.angle);
	doom->player.anglecos = cos(doom->player.angle);
	ft_move_wsad(doom, &doom->move, &doom->player);
}