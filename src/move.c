/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 10:12:00 by lde-batz          #+#    #+#             */
/*   Updated: 2019/05/04 18:20:16 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	update_velocity2(t_doom *doom, t_player *player, t_xy *move_vec
																, float speed)
{
	float acc;

	if (doom->keys.right == 1)
	{
		move_vec->x += player->anglesin * speed;
		move_vec->y -= player->anglecos * speed;
	}
	if (doom->keys.left == 1)
	{
		move_vec->x -= player->anglesin * speed;
		move_vec->y += player->anglecos * speed;
	}
	player->moving = doom->keys.right || doom->keys.left
		|| doom->keys.up || doom->keys.down;
	acc = player->moving ? 0.4 : 0.2;
	player->velocity.x = player->velocity.x * (1 - acc) + move_vec->x * acc;
	player->velocity.y = player->velocity.y * (1 - acc) + move_vec->y * acc;
}

void	update_velocity(t_doom *doom, t_player *player)
{
	t_xy	move_vec;
	float	speed;

	speed = 0.1;
	if (doom->you.is_sprinting)
		speed *= 2;
	if (doom->you.is_crouching)
		speed /= 2;
	move_vec.x = 0.0;
	move_vec.y = 0.0;
	if (doom->keys.up == 1)
	{
		move_vec.x += player->anglecos * speed;
		move_vec.y += player->anglesin * speed;
	}
	if (doom->keys.down == 1)
	{
		move_vec.x -= player->anglecos * speed;
		move_vec.y -= player->anglesin * speed;
	}
	update_velocity2(doom, player, &move_vec, speed);
}

void	moving2(t_doom *d)
{
	t_xy	dest;
	float	t1;

	t1 = COL;
	dest.x = d->you.pos.x + d->you.velocity.x;
	dest.y = d->you.pos.y + d->you.velocity.y;
	if (d->nmap->map[(int)(d->you.pos.y - t1)][(int)(dest.x + t1)].collides
	|| d->nmap->map[(int)(d->you.pos.y + t1)][(int)(dest.x - t1)].collides
	|| d->nmap->map[(int)(d->you.pos.y + t1)][(int)(dest.x + t1)].collides
	|| d->nmap->map[(int)(d->you.pos.y - t1)][(int)(dest.x - t1)].collides)
		d->you.velocity.x = 0;
	if (d->nmap->map[(int)(dest.y + t1)][(int)(d->you.pos.x - t1)].collides
	|| d->nmap->map[(int)(dest.y - t1)][(int)(d->you.pos.x + t1)].collides
	|| d->nmap->map[(int)(dest.y + t1)][(int)(d->you.pos.x + t1)].collides
	|| d->nmap->map[(int)(dest.y - t1)][(int)(d->you.pos.x - t1)].collides)
		d->you.velocity.y = 0;
	if (d->you.velocity.x != 0 && d->you.velocity.y != 0)
		if (d->nmap->map[(int)(dest.y + t1)][(int)(dest.x + t1)].collides
		|| d->nmap->map[(int)(dest.y - t1)][(int)(dest.x - t1)].collides
		|| d->nmap->map[(int)(dest.y - t1)][(int)(dest.x + t1)].collides
		|| d->nmap->map[(int)(dest.y + t1)][(int)(dest.x - t1)].collides)
		{
			d->you.velocity.x = 0;
			d->you.velocity.y = 0;
		}
}

void	moving(t_doom *doom)
{
	int		channel;

	if (doom->you.moving)
	{
		channel = Mix_PlayChannel(-1, doom->scores.walk, 0);
		if (channel != 0)
			Mix_HaltChannel(channel);
	}
	moving2(doom);
	doom->you.pos.x += doom->you.velocity.x;
	doom->you.pos.y += doom->you.velocity.y;
}
