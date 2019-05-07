/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:04:07 by lde-batz          #+#    #+#             */
/*   Updated: 2019/05/07 23:38:34 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		check_wall(t_doom *d, t_list *sprites, t_sprite *sprite, t_xy *dest)
{
	if (d->nmap->map[(int)(sprite->pos.y - COL)][(int)(dest->x + COL)].collides
	|| d->nmap->map[(int)(sprite->pos.y + COL)][(int)(dest->x - COL)].collides
	|| d->nmap->map[(int)(sprite->pos.y + COL)][(int)(dest->x + COL)].collides
	|| d->nmap->map[(int)(sprite->pos.y - COL)][(int)(dest->x - COL)].collides)
		lstcontainer_remove(d->nmap->sprites, sprites);
	else if (d->nmap->map[(int)(dest->y + COL)]
	[(int)(sprite->pos.x - COL)].collides
	|| d->nmap->map[(int)(dest->y - COL)][(int)(sprite->pos.x + COL)].collides
	|| d->nmap->map[(int)(dest->y + COL)][(int)(sprite->pos.x + COL)].collides
	|| d->nmap->map[(int)(dest->y - COL)][(int)(sprite->pos.x - COL)].collides)
		lstcontainer_remove(d->nmap->sprites, sprites);
	else if (d->nmap->map[(int)(dest->y + COL)][(int)(dest->x + COL)].collides
	|| d->nmap->map[(int)(dest->y - COL)][(int)(dest->x - COL)].collides
	|| d->nmap->map[(int)(dest->y - COL)][(int)(dest->x + COL)].collides
	|| d->nmap->map[(int)(dest->y + COL)][(int)(dest->x - COL)].collides)
		lstcontainer_remove(d->nmap->sprites, sprites);
	else
		return (1);
	return (0);
}

int		check_other_sprites(t_doom *doom, t_list *sprites, t_xy *dest)
{
	t_list		*o_sprites;
	t_sprite	*o_sprite;

	o_sprites = doom->nmap->sprites->firstelement;
	while (o_sprites)
	{
		o_sprite = o_sprites->content;
		if (o_sprite->collides
		&& dest->x < o_sprite->pos.x + 0.2 + COL
		&& dest->x > o_sprite->pos.x - 0.2 - COL
		&& dest->y < o_sprite->pos.y + 0.2 + COL
		&& dest->y > o_sprite->pos.y - 0.2 - COL)
		{
			lstcontainer_remove(doom->nmap->sprites, sprites);
			return (0);
		}
		o_sprites = o_sprites->next;
	}
	return (1);
}

void	move_sprite(t_doom *doom, t_list *sprites, t_sprite *sprite, int *supp)
{
	t_xy	dest;

	dest.x = sprite->pos.x + sprite->vel.x;
	dest.y = sprite->pos.y + sprite->vel.y;
	if (check_wall(doom, sprites, sprite, &dest)
	&& check_other_sprites(doom, sprites, &dest))
	{
		sprite->pos.x = dest.x;
		sprite->pos.y = dest.y;
		sprite->pos.z += sprite->vel.z;
	}
	else
	{
		*supp = 1;
		doom->lsprite.numbSprites--;
	}
}

void	moving_sprite(t_doom *doom)
{
	t_list		*sprites;
	t_sprite	*sprite;
	t_list		*tmp;
	int			supp;

	sprites = doom->nmap->sprites->firstelement;
	while (sprites)
	{
		sprite = sprites->content;
		tmp = sprites->prev;
		supp = 0;
		if (sprite->vel.x != 0 || sprite->vel.y != 0 || sprite->vel.z != 0)
			move_sprite(doom, sprites, sprite, &supp);
		if (supp == 0)
			sprites = sprites->next;
		else if (tmp)
			sprites = tmp->next;
		else
			sprites = doom->nmap->sprites->firstelement;
	}
}
