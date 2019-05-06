/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 10:12:00 by lde-batz          #+#    #+#             */
/*   Updated: 2019/05/06 15:23:28 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

float	point_side(t_xy p, t_vec p1, t_xy p2)
{
	float	side;

	side = (p2.x - p1.x) * (p.y - p1.y) - (p.x - p1.x) * (p2.y - p1.y);
	return (side);
}

void	moving_diagonal(t_doom *doom, t_xy *dest, t_xy pt)
{
	float side;

	side = point_side(pt, doom->you.pos, *dest);
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
			moving_diagonal(d, &dest, pt_angle(d));
}

void	moving(t_doom *doom)
{
	t_xy		dest;
	t_sprite	*sprite;
	int			del;

	if (!(sprite = (t_sprite*)mmalloc(sizeof(t_sprite))))
		exit_program(doom, ERROR_MEMORY);
	sprite->pos.x = 3.5;
	sprite->pos.y = 3.5;
	sprite->collides = 1;
//	sprite->type = sprite_ammo;
//	sprite->obtainable = 1;
	if (doom->you.moving)
		if (Mix_Playing(0) == 0)
			Mix_PlayChannel(0, doom->musics.walk, 0);
	moving2(doom);
	while ((doom->you.velocity.x != 0 || doom->you.velocity.y != 0) && sprite)
	{
		dest.x = doom->you.pos.x + doom->you.velocity.x;
		dest.y = doom->you.pos.y + doom->you.velocity.y;
		if (dest.x < sprite->pos.x + 0.2 + COL
		&& dest.x > sprite->pos.x - 0.2 - COL
		&& dest.y < sprite->pos.y + 0.2 + COL
		&& dest.y > sprite->pos.y - 0.2 - COL)
			check_sprite(doom, sprite, &dest);
		sprite = NULL;
	}
	doom->you.pos.x += doom->you.velocity.x;
	doom->you.pos.y += doom->you.velocity.y;
}
