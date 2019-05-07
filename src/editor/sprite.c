/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 11:11:17 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 18:57:40 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "editor.h"

t_sprite_type	*get_sprite_type(t_doom *d, int type)
{
	t_list			*tmp;
	t_sprite_type	*tmp_sprite;

	tmp = d->sprite_types->firstelement;
	while (tmp)
	{
		tmp_sprite = tmp->content;
		if (tmp_sprite->sprite_type == type)
			return (tmp_sprite);
		tmp = tmp->next;
	}
	return (d->sprite_types->firstelement->content);
}

void		remove_sprite(t_doom *d, t_list *s)
{
	lstcontainer_remove(d->nmap->sprites, s);
	d->nmap->spritecount = lstcontainer_size(d->nmap->sprites);
	d->lsprite.numbSprites = d->nmap->spritecount;
	d->editor.selected_sprite = NULL;
	switch_tool(d, tool_none, NULL);
}

void		add_sprite(t_doom *d, int x, int y)
{
	t_sprite	*s;

	if (!(s = mmalloc(sizeof(t_sprite))))
		exit_program(d, ERROR_SDL_AFTER_INIT);
	s->base_x = x;
	s->base_y = y;
	s->collides = d->editor.foc_s.b_collides;
	s->obtainable = d->editor.foc_s.b_obtainable;
	s->pos.x = (float)x + 0.5;
	s->pos.y = (float)y + 0.5;
	s->texture = d->editor.foc_s.b_texture;
	s->texture_back = d->editor.foc_s.b_texture_back;
	s->type = d->editor.foc_s.b_type;
	lstcontainer_add(d->nmap->sprites, s);
	d->nmap->spritecount = lstcontainer_size(d->nmap->sprites);
	d->lsprite.numbSprites = d->nmap->spritecount;
	d->editor.selected_sprite = NULL;
}

void		update_interactions_sprite(t_doom *d)
{
	t_editor *e;

	e = &d->editor;
	e->rbr_quadrant.orient_hor->background_color = e->foc.b_orientation == 0 ? e->select_color : e->base_color;
	e->rbr_quadrant.orient_ver->background_color = e->foc.b_orientation == 1 ? e->select_color : e->base_color;
	e->rbr_quadrant.has_celng->checked = e->foc.b_has_ceiling;
	wjauge_set(d, e->rbr_quadrant.ev_id, e->foc.b_event_id, 1);
	wjauge_set(d, e->rbr_quadrant.sc_height, e->foc.b_ceiling_height, 1);
	wjauge_set(d, e->rbr_quadrant.b_w, e->foc.b_x_size, 1);
	wjauge_set(d, e->rbr_quadrant.b_h, e->foc.b_y_size, 1);
}

void		select_sprite_type(t_doom *d, t_sprite_type *type)
{
	d->editor.selected_sprite = type;
	d->editor.foc_s.b_type = type->sprite_type;
	update_interactions_sprite(d);
}