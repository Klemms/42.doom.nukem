/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:04:07 by lde-batz          #+#    #+#             */
/*   Updated: 2019/05/06 15:17:07 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	collision_sprites(t_doom *doom, t_sprite *sprite, t_xy *dest)
{
	t_xy	pt;

	if (doom->you.velocity.x == 0)
		doom->you.velocity.y = 0;
	else if (doom->you.velocity.y == 0)
		doom->you.velocity.x = 0;
	else if (doom->you.pos.x < sprite->pos.x + 0.2 + COL
	&& doom->you.pos.x > sprite->pos.x - 0.2 - COL)
		doom->you.velocity.y = 0;
	else if (doom->you.pos.y < sprite->pos.y + 0.2 + COL
	&& doom->you.pos.y > sprite->pos.y - 0.2 - COL)
		doom->you.velocity.x = 0;
	else
	{
		if (doom->you.velocity.x < 0)
			pt.x = sprite->pos.x + 0.2 + COL;
		else
			pt.x = sprite->pos.x - 0.2 - COL;
		if (doom->you.velocity.y < 0)
			pt.y = sprite->pos.y + 0.2 + COL;
		else
			pt.y = sprite->pos.y - 0.2 - COL;
		moving_diagonal(doom, dest, pt);
	}
}

void	check_sprite(t_doom *doom, t_sprite *sprite, t_xy *dest)
{
	int	del;

	if (sprite->collides)
		collision_sprites(doom, sprite, dest);
	else if (sprite->obtainable)
	{
		del = 1;
		if (sprite->type == sprite_key)
			doom->you.hud.key = 1;
		else if (sprite->type == sprite_ammo)
			doom->you.hud.ammo += 10;
		else if (sprite->type == sprite_health)
		{
			if (doom->you.hud.health == 100)
				del = 0;
			else if (doom->you.hud.health > 90)
				doom->you.hud.health = 100;
			else
				doom->you.hud.health += 10;
		}
	}
}
