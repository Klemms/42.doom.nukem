/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 10:14:58 by lde-batz          #+#    #+#             */
/*   Updated: 2019/03/19 15:17:39 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	ft_event(t_doom *doom)
{
	if (doom->event.type == SDL_KEYDOWN || doom->event.type == SDL_KEYUP)
	{
		if (doom->event.key.keysym.sym == SDLK_ESCAPE)
			doom->bool_prog = SDL_FALSE;
		else if (doom->event.key.keysym.sym == SDLK_w)
			doom->move.wsad[0] = (doom->event.type == SDL_KEYDOWN) ? 1 : 0;
		else if (doom->event.key.keysym.sym == SDLK_s)
			doom->move.wsad[1] = (doom->event.type == SDL_KEYDOWN) ? 1 : 0;
		else if (doom->event.key.keysym.sym == SDLK_a)
			doom->move.wsad[2] = (doom->event.type == SDL_KEYDOWN) ? 1 : 0;
		else if (doom->event.key.keysym.sym == SDLK_d)
			doom->move.wsad[3] = (doom->event.type == SDL_KEYDOWN) ? 1 : 0;
		else if (doom->event.key.keysym.sym == SDLK_SPACE)
		{
			if (doom->move.ground)
			{
				printf("jump\n");
				doom->player.velocity.z += 0.5;
				doom->move.falling = 1;
			}
		}
		else if (doom->event.key.keysym.sym == SDLK_LSHIFT)
		{
			doom->move.ducking = (doom->event.type == SDL_KEYDOWN) ? 1 : 0;
			doom->move.speed = (doom->event.type == SDL_KEYDOWN) ? 0.3 : 1;
			doom->move.falling = 1;
		}
		else if (doom->event.key.keysym.sym == SDLK_x)
			doom->move.speed = (doom->event.type == SDL_KEYDOWN) ? 2 : 1;
	}
	else if (doom->event.type == SDL_QUIT)
		doom->bool_prog = SDL_FALSE;
	else if (doom->event.type == SDL_MOUSEMOTION)
		ft_move_mouse(doom);
}
