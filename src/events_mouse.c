/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:18:54 by lde-batz          #+#    #+#             */
/*   Updated: 2019/05/07 13:47:37 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		mouse_down(t_doom *doom, SDL_Event event)
{
	int		channel;

	if (event.button.button == SDL_BUTTON_LEFT)
	{
		if (doom->you.hud.ammo > 0)
		{
			Mix_PlayChannel(1, doom->musics.shot, 0);
			Mix_FadeOutChannel(channel, 680);
			doom->you.hud.ammo -= 1;
		}
	}
	return (1);
}

int		mouse_up(t_doom *doom, SDL_Event event)
{
	return (1);
}
