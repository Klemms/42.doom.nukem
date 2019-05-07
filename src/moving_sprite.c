/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:04:07 by lde-batz          #+#    #+#             */
/*   Updated: 2019/05/07 20:31:44 by lde-batz         ###   ########.fr       */
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

void	check_sprite(t_doom *doom, t_list *sprites, t_sprite *sprite, t_xy *dest)
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
		{
			lstcontainer_remove(doom->nmap->sprites, sprites);
			doom->lsprite.numbSprites--;
		}
	}
	if (sprite->type == sprite_damage)
		check_damage(doom);
}

int	check_wall(t_doom *doom, t_list *sprites, t_sprite *sprite, t_xy *dest)
{
	if (doom->nmap->map[(int)(sprite->pos.y - COL)][(int)(dest->x + COL)].collides
	|| doom->nmap->map[(int)(sprite->pos.y + COL)][(int)(dest->x - COL)].collides
	|| doom->nmap->map[(int)(sprite->pos.y + COL)][(int)(dest->x + COL)].collides
	|| doom->nmap->map[(int)(sprite->pos.y - COL)][(int)(dest->x - COL)].collides)
		lstcontainer_remove(doom->nmap->sprites, sprites);
	else if (doom->nmap->map[(int)(dest->y + COL)][(int)(sprite->pos.x - COL)].collides
	|| doom->nmap->map[(int)(dest->y - COL)][(int)(sprite->pos.x + COL)].collides
	|| doom->nmap->map[(int)(dest->y + COL)][(int)(sprite->pos.x + COL)].collides
	|| doom->nmap->map[(int)(dest->y - COL)][(int)(sprite->pos.x - COL)].collides)
		lstcontainer_remove(doom->nmap->sprites, sprites);
	else if (doom->nmap->map[(int)(dest->y + COL)][(int)(dest->x + COL)].collides
	|| doom->nmap->map[(int)(dest->y - COL)][(int)(dest->x - COL)].collides
	|| doom->nmap->map[(int)(dest->y - COL)][(int)(dest->x + COL)].collides
	|| doom->nmap->map[(int)(dest->y + COL)][(int)(dest->x - COL)].collides)
		lstcontainer_remove(doom->nmap->sprites, sprites);
	else
		return (1);
	return (0);
}

int	check_other_sprites(t_doom *doom, t_list *sprites, t_sprite *sprite, t_xy *dest)
{
	t_list		*o_sprites;
	t_sprite	*o_sprite;
	
	(void)sprite;
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

void	moving_sprite(t_doom *doom)
{
	t_list		*sprites;
	t_sprite	*sprite;
	t_xy		dest;
	t_list		*tmp;
	int			sup;

	sprites = doom->nmap->sprites->firstelement;
	while (sprites)
	{
		sprite = sprites->content;
		tmp = sprites->prev;
		sup = 0;
		if (sprite->vel.x != 0 || sprite->vel.y != 0 || sprite->vel.z != 0)
		{
			dest.x = sprite->pos.x + sprite->vel.x;
			dest.y = sprite->pos.y + sprite->vel.y;
			if (check_wall(doom, sprites, sprite, &dest)
			&& check_other_sprites(doom, sprites, sprite, &dest))
			{
				sprite->pos.x = dest.x;
				sprite->pos.y = dest.y;
				sprite->pos.z += sprite->vel.z;
			}
			else
			{
				sup = 1;
				doom->lsprite.numbSprites--;
			}
			
		}
		if (sup == 0)
			sprites = sprites->next;
		else if (tmp)
			sprites = tmp->next;
		else
			sprites = doom->nmap->sprites->firstelement;
	}
}
