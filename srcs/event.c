/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 10:14:58 by lde-batz          #+#    #+#             */
/*   Updated: 2019/03/19 19:34:36 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	ft_check_duck_up(t_doom *doom)
{
	if (doom->move.duck_up == 1
		&& CAM_H + COLLISION_HEAD < doom->sectors[doom->player.sector].ceil
		- doom->sectors[doom->player.sector].floor)
	{
		doom->move.ducking = 0;
		doom->move.speed = 1;
		doom->move.falling = 1;
		doom->move.duck_up = 0;
	}
}

void	ft_check_duck(t_doom *doom)
{
	if (doom->event.type == SDL_KEYUP
		&& CAM_H + COLLISION_HEAD > doom->sectors[doom->player.sector].ceil
		- doom->sectors[doom->player.sector].floor)
	{
		doom->move.duck_up = 1;
		doom->event.type = SDL_KEYDOWN;
	}
}

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
				doom->player.velocity.z += 0.5;
				doom->move.falling = 1;
			}
		}
		else if (doom->event.key.keysym.sym == SDLK_LSHIFT)
		{
			ft_check_duck(doom);
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
