/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 22:18:06 by lde-batz          #+#    #+#             */
/*   Updated: 2019/05/07 23:20:11 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	check_damage(t_doom *doom)
{
	if (Mix_Playing(2) == 0)
	{
		Mix_PlayChannel(2, doom->musics.damage, 0);
		if (doom->you.hud.health - 10 > 0)
			doom->you.hud.health -= 10;
		else
			exit_program(doom, ERROR_DEAD);
	}
}

int		check_health(t_doom *doom)
{
	if (doom->you.hud.health == 100)
		return (0);
	else
	{
		doom->you.hud.health += 10;
		return (1);
	}
}

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

int		check_sprite(t_doom *doom, t_list *sprites, t_sprite *sprite,
																	t_xy *dest)
{
	int	del;

	if (sprite->type == sprite_damage)
		check_damage(doom);
	if (sprite->collides)
		collision_sprites(doom, sprite, dest);
	else if (sprite->obtainable)
	{
		del = 1;
		if (sprite->type == sprite_key)
			doom->you.hud.key += 1;
		else if (sprite->type == sprite_ammo)
			doom->you.hud.ammo += 10;
		else if (sprite->type == sprite_health)
			del = check_health(doom);
		if (del)
		{
			lstcontainer_remove(doom->nmap->sprites, sprites);
			doom->lsprite.numbSprites--;
			return (1);
		}
	}
	return (0);
}

void	moving2(t_doom *d)
{
	t_xy	dest;

	if (d->you.moving)
		if (Mix_Playing(0) == 0)
			Mix_PlayChannel(0, d->musics.walk, 0);
	dest.x = d->you.pos.x + d->you.velocity.x;
	dest.y = d->you.pos.y + d->you.velocity.y;
	if (d->nmap->map[(int)(d->you.pos.y - COL)][(int)(dest.x + COL)].collides
	|| d->nmap->map[(int)(d->you.pos.y + COL)][(int)(dest.x - COL)].collides
	|| d->nmap->map[(int)(d->you.pos.y + COL)][(int)(dest.x + COL)].collides
	|| d->nmap->map[(int)(d->you.pos.y - COL)][(int)(dest.x - COL)].collides)
		d->you.velocity.x = 0;
	if (d->nmap->map[(int)(dest.y + COL)][(int)(d->you.pos.x - COL)].collides
	|| d->nmap->map[(int)(dest.y - COL)][(int)(d->you.pos.x + COL)].collides
	|| d->nmap->map[(int)(dest.y + COL)][(int)(d->you.pos.x + COL)].collides
	|| d->nmap->map[(int)(dest.y - COL)][(int)(d->you.pos.x - COL)].collides)
		d->you.velocity.y = 0;
	if (d->you.velocity.x != 0 && d->you.velocity.y != 0)
		if (d->nmap->map[(int)(dest.y + COL)][(int)(dest.x + COL)].collides
		|| d->nmap->map[(int)(dest.y - COL)][(int)(dest.x - COL)].collides
		|| d->nmap->map[(int)(dest.y - COL)][(int)(dest.x + COL)].collides
		|| d->nmap->map[(int)(dest.y + COL)][(int)(dest.x - COL)].collides)
			moving_diagonal(d, &dest, pt_angle(d));
}
