/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 10:12:00 by lde-batz          #+#    #+#             */
/*   Updated: 2019/05/06 12:00:01 by cababou          ###   ########.fr       */
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
	acc = player->moving ? 0.4 : 0.3;
	player->velocity.x = player->velocity.x * (1 - acc) + move_vec->x * acc;
	player->velocity.y = player->velocity.y * (1 - acc) + move_vec->y * acc;
}

void	update_velocity(t_doom *doom, t_player *player)
{
	t_xy	move_vec;
	float	speed;

	speed = 0.1;
	if ((doom->keys.up == 1 || doom->keys.down == 1) && (doom->keys.left == 1
	|| doom->keys.right == 1))
		speed = 0.07071;
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

float	point_side(t_xy p, t_vec p1, t_xy p2)
{
	float	side;

	side = (p2.x - p1.x) * (p.y - p1.y) - (p.x - p1.x) * (p2.y - p1.y);
	return (side);
}

void	moving_diagonal(t_doom *doom, t_xy dest, t_xy pt)
{
	float side;

	side = point_side(pt, doom->you.pos, dest);
	if ((doom->you.velocity.x < 0 && doom->you.velocity.y < 0) 
	|| (doom->you.velocity.x > 0 && doom->you.velocity.y > 0))
	{
		if (side > 0)
			doom->you.velocity.y = 0;
		else
			doom->you.velocity.x = 0;
	}
	else
	{
		if (side > 0)
			doom->you.velocity.x = 0;
		else
			doom->you.velocity.y = 0;
	}
}

t_xy	pt_angle(t_doom *doom)
{
	t_xy	pt;

	if (doom->you.velocity.x < 0)
		pt.x = (int)doom->you.pos.x + COL;
	else
		pt.x = (int)doom->you.pos.x + 1 - COL;
	if (doom->you.velocity.y < 0)
		pt.y = (int)doom->you.pos.y + COL;
	else
		pt.y = (int)doom->you.pos.y + 1 - COL;
	return (pt);
}

void	moving2(t_doom *d)
{
	t_xy	dest;
	float	side;

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
			moving_diagonal(d, dest, pt_angle(d));
}

void	collision_sprites(t_doom *doom, t_sprite *sprite, t_xy dest)
{
	t_xy		pt;
	
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

void	moving(t_doom *doom)
{
	t_xy		dest;
	t_sprite	*sprite;

	if (!(sprite = (t_sprite*)mmalloc(sizeof(t_sprite))))
		exit_program(doom, ERROR_MEMORY);
	sprite->pos.x = 3.5;
	sprite->pos.y = 3.5;
	sprite->collides = 1;
//	doom->textures = lstcontainer_new();
//	lstcontainer_add(doom->textures, FOIDSHFOSDFSD);
//	ft_lstget_fromelement(112, doom->textures->firstelement);

	if (doom->you.moving)
		if (Mix_Playing(0) == 0)
			Mix_PlayChannel(0, doom->scores.walk, 0);
	moving2(doom);
	while((doom->you.velocity.x != 0 || doom->you.velocity.y != 0) && sprite)
	{
		if (sprite->collides)
		{
			dest.x = doom->you.pos.x + doom->you.velocity.x;
			dest.y = doom->you.pos.y + doom->you.velocity.y;
			if (dest.x < sprite->pos.x + 0.2 + COL
			&& dest.x > sprite->pos.x - 0.2 - COL
			&& dest.y < sprite->pos.y + 0.2 + COL
			&& dest.y > sprite->pos.y - 0.2 - COL)
				collision_sprites(doom, sprite, dest);
		}
		sprite = NULL;
	}
	doom->you.pos.x += doom->you.velocity.x;
	doom->you.pos.y += doom->you.velocity.y;
}
