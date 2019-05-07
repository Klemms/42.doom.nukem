/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritesetter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 18:03:10 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 18:37:16 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"


t_sprite	*make_sprite(t_doom *d, int spritetype, int x, int y)
{
	t_sprite	*s;

	if (!(s = mmalloc(sizeof(t_sprite))))
		exit_program(d, ERROR_SDL_AFTER_INIT);
	s->base_x = x;
	s->base_y = y;
	s->type = spritetype;
	s->pos.x = ((float)x) + 0.5;
	s->pos.y = ((float)y) + 0.5;
	return (s);
}

t_sprite	*find_sprite(t_doom *d, int x, int y, int rm)
{
	t_list			*tmp;
	t_sprite		*tmp_sprite;

	tmp = d->nmap->sprites->firstelement;
	while (tmp)
	{
		tmp_sprite = tmp->content;
		if (tmp_sprite->base_x == x && tmp_sprite->base_y == y
			&& rm == tmp_sprite->render_mode)
			return (tmp_sprite);
		tmp = tmp->next;
	}
	return (NULL);
}

void	blockwindowdoor_added(t_doom *d, t_mblock *b)
{
	t_sprite	*s;

	if (b->block_type == block_door && !find_sprite(d, b->x, b->y, rend_door))
	{
		s = make_sprite(d, sprite_dummy, b->x, b->y);
		s->render_mode = rend_door;
		s->texture = b->n_texture;
		s->texture_back = b->s_texture;
		s->dontsave = 1;
		lstcontainer_add(d->nmap->sprites, s);
		d->nmap->spritecount = lstcontainer_size(d->nmap->sprites);
		d->lsprite.numbSprites = d->nmap->spritecount;
	}
	if (b->block_type == block_window
		&& !find_sprite(d, b->x, b->y, rend_window))
	{
		s = make_sprite(d, sprite_dummy, b->x, b->y);
		s->render_mode = rend_window;
		s->texture = b->n_texture;
		s->dontsave = 1;
		s->texture_back = b->s_texture;
		lstcontainer_add(d->nmap->sprites, s);
		d->nmap->spritecount = lstcontainer_size(d->nmap->sprites);
		d->lsprite.numbSprites = d->nmap->spritecount;
	}
}

void	blockwindowdoor_removed(t_doom *d, int type, int x, int y)
{
	t_list			*tmp;
	t_sprite		*tmp_sprite;

	tmp = d->nmap->sprites->firstelement;
	while (tmp)
	{
		tmp_sprite = tmp->content;
		if (tmp_sprite->base_x == x && tmp_sprite->base_y == y)
		{
			if (type == block_door && tmp_sprite->render_mode == rend_door)
			{
				remove_sprite(d, tmp);
				break;
			}
			else if (type == block_window
				&& tmp_sprite->render_mode == rend_window)
			{
				remove_sprite(d, tmp);
				break;
			}
		}
		tmp = tmp->next;
	}
}
