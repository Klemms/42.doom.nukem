/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_sprite2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 00:01:47 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/08 01:02:18 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	del_sprite_mov(t_doom *doom, t_list *sprites)
{
	lstcontainer_remove(doom->nmap->sprites, sprites);
	doom->lsprite.numbSprites--;
}

void	check_sprite(t_doom *doom, t_list *sprites,
	t_sprite *sprite, t_xy *dest)
{
	int	del;

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
		{
			if (doom->you.hud.health == 100)
				del = 0;
			else
				doom->you.hud.health += 10;
		}
		if (del)
			del_sprite_mov(doom, sprites);
	}
	if (sprite->type == sprite_damage)
		check_damage(doom);
}

int		check_wall(t_doom *doom, t_list *sprites, t_sprite *s, t_xy *d)
{
	if (doom->nmap->map[(int)(s->pos.y - COL)][(int)(d->x + COL)].collides
	|| doom->nmap->map[(int)(s->pos.y + COL)][(int)(d->x - COL)].collides
	|| doom->nmap->map[(int)(s->pos.y + COL)][(int)(d->x + COL)].collides
	|| doom->nmap->map[(int)(s->pos.y - COL)][(int)(d->x - COL)].collides)
		lstcontainer_remove(doom->nmap->sprites, sprites);
	else if (doom->nmap->map[(int)(d->y + COL)][(int)(s->pos.x - COL)].collides
	|| doom->nmap->map[(int)(d->y - COL)][(int)(s->pos.x + COL)].collides
	|| doom->nmap->map[(int)(d->y + COL)][(int)(s->pos.x + COL)].collides
	|| doom->nmap->map[(int)(d->y - COL)][(int)(s->pos.x - COL)].collides)
		lstcontainer_remove(doom->nmap->sprites, sprites);
	else if (doom->nmap->map[(int)(d->y + COL)][(int)(d->x + COL)].collides
	|| doom->nmap->map[(int)(d->y - COL)][(int)(d->x - COL)].collides
	|| doom->nmap->map[(int)(d->y - COL)][(int)(d->x + COL)].collides
	|| doom->nmap->map[(int)(d->y + COL)][(int)(d->x - COL)].collides)
		lstcontainer_remove(doom->nmap->sprites, sprites);
	else
		return (1);
	return (0);
}
