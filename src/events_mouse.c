/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:18:54 by lde-batz          #+#    #+#             */
/*   Updated: 2019/05/06 15:25:05 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		mouse_down(t_doom *doom, SDL_Event event)
{
	int		channel;

	if (event.button.button == SDL_BUTTON_LEFT && doom->you.is_shooting == 0)
	{
		if (Mix_Playing(1) == 0)
		{
			Mix_PlayChannel(1, doom->musics.shot, 0);
			Mix_FadeOutChannel(channel, 680);
			doom->you.is_shooting = 1;
		}
		else
			doom->you.is_shooting = 0;
	}
	return (1);
}

int		mouse_up(t_doom *doom, SDL_Event event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
		doom->you.is_shooting = 0;
	return (1);
}
