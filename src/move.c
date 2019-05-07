/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 10:12:00 by lde-batz          #+#    #+#             */
/*   Updated: 2019/05/07 23:38:50 by lde-batz         ###   ########.fr       */
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

t_list	*next_supp(t_doom *doom, t_list *sprites, t_list *tmp, int supp)
{
	if (supp == 0)
		return (sprites->next);
	else if (tmp)
		return (tmp->next);
	else
		return (doom->nmap->sprites->firstelement);
}

void	moving(t_doom *doom)
{
	t_xy		dest;
	t_list		*sprites;
	t_list		*tmp;
	t_sprite	*sprite;
	int			supp;

	sprites = doom->nmap->sprites->firstelement;
	moving2(doom);
	while ((doom->you.velocity.x != 0 || doom->you.velocity.y != 0) && sprites)
	{
		supp = 0;
		tmp = sprites->prev;
		sprite = sprites->content;
		dest.x = doom->you.pos.x + doom->you.velocity.x;
		dest.y = doom->you.pos.y + doom->you.velocity.y;
		if (dest.x < sprite->pos.x + 0.2 + COL
		&& dest.x > sprite->pos.x - 0.2 - COL
		&& dest.y < sprite->pos.y + 0.2 + COL
		&& dest.y > sprite->pos.y - 0.2 - COL)
			check_sprite(doom, sprites, sprite, &dest);
		sprites = next_supp(doom, sprites, tmp, supp);
	}
	doom->you.pos.x += doom->you.velocity.x;
	doom->you.pos.y += doom->you.velocity.y;
}
