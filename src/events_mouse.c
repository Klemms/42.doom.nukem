/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:18:54 by lde-batz          #+#    #+#             */
/*   Updated: 2019/05/08 01:55:56 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	shooting(t_doom *doom)
{
	t_sprite *new;

	if (!(new = (t_sprite*)mmalloc(sizeof(t_sprite))))
		exit_program(doom, ERROR_MEMORY);
	new->type = sprite_bullet;
	new->vel.x = doom->you.dir.x * 0.3;
	new->vel.y = doom->you.dir.y * 0.3;
	new->vel.z = doom->you.pitch - 0.5;
	new->pos.x = doom->you.pos.x + new->vel.x;
	new->pos.y = doom->you.pos.y + new->vel.y;
	lstcontainer_add(doom->nmap->sprites, new);
	doom->lsprite.numbSprites++;
}

int		mouse_down(t_doom *doom, SDL_Event event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		if (doom->you.hud.ammo > 0)
		{
			Mix_PlayChannel(1, doom->musics.shot, 0);
			doom->you.hud.ammo -= 1;
			shooting(doom);
		}
	}
	return (1);
}
