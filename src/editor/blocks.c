/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 08:44:57 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 18:47:47 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		set_to_default_mblock(t_mblock *dest, int x, int y)
{
	dest->block_type = block_wall;
	dest->orientation = 0;
	dest->x_size = 100;
	dest->y_size = 100;
	dest->event_id = 0;
	dest->ceiling_height = 100;
	dest->has_ceiling = 1;
	dest->ceilng_tex = 2;
	dest->floor_tex = 1;
	dest->n_texture = 0;
	dest->s_texture = 1;
	dest->w_texture = 2;
	dest->e_texture = 3;
	dest->light = -1;
	dest->collides = 1;
	dest->x = x;
	dest->y = y;
}

void		copy_block(t_mblock *dest, t_mblock *src, int free2, int cpcrds)
{
	dest->block_type = src->block_type;
	dest->orientation = src->orientation;
	dest->x_size = src->x_size;
	dest->y_size = src->y_size;
	dest->event_id = src->event_id;
	dest->ceiling_height = src->ceiling_height;
	dest->has_ceiling = src->has_ceiling;
	dest->ceilng_tex = src->ceilng_tex;
	dest->floor_tex = src->floor_tex;
	dest->n_texture = src->n_texture;
	dest->s_texture = src->s_texture;
	dest->w_texture = src->w_texture;
	dest->e_texture = src->e_texture;
	dest->light = src->light;
	dest->collides = src->collides;
	if (cpcrds)
	{
		dest->x = src->x;
		dest->y = src->y;
	}
	if (free2)
		free(src);
}

void		update_interactions(t_doom *d)
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

void		select_block_type(t_doom *d, t_block_type *type)
{
	d->editor.selected_block = type;
	d->editor.foc.b_block_type = type->block_type;
	update_interactions(d);
}

void		copy_block_type(t_doom *d, t_block_type *type, t_mblock *blk)
{
	d->editor.selected_block = type;
	d->editor.foc.b_block_type = blk->block_type;
	d->editor.foc.b_orientation = blk->orientation;
	d->editor.foc.b_x_size = blk->x_size;
	d->editor.foc.b_y_size = blk->y_size;
	d->editor.foc.b_event_id = blk->event_id;
	d->editor.foc.b_ceiling_height = blk->ceiling_height;
	d->editor.foc.b_has_ceiling = blk->has_ceiling;
	d->editor.foc.b_ceilng_tex = blk->ceilng_tex;
	d->editor.foc.b_floor_tex = blk->floor_tex;
	d->editor.foc.b_n_texture = blk->n_texture;
	d->editor.foc.b_s_texture = blk->s_texture;
	d->editor.foc.b_w_texture = blk->w_texture;
	d->editor.foc.b_e_texture = blk->e_texture;
	d->editor.foc.b_light = blk->light;
	d->editor.foc.b_collides = blk->collides;
	update_interactions(d);
}
