/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 08:44:57 by cababou           #+#    #+#             */
/*   Updated: 2019/05/03 09:33:49 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		update_interactions(t_doom *d)
{
	t_editor *e;

	e = &d->editor;
	e->rbr_quadrant.orient_n->background_color = e->foc.b_orientation == 0 ? e->select_color : e->base_color;
	e->rbr_quadrant.orient_s->background_color = e->foc.b_orientation == 1 ? e->select_color : e->base_color;
	e->rbr_quadrant.orient_w->background_color = e->foc.b_orientation == 2 ? e->select_color : e->base_color;
	e->rbr_quadrant.orient_e->background_color = e->foc.b_orientation == 3 ? e->select_color : e->base_color;
	e->rbr_quadrant.has_celng->checked = e->foc.b_has_ceiling;
	wjauge_set(d, e->rbr_quadrant.s_height, e->foc.b_height, 1);
	wjauge_set(d, e->rbr_quadrant.sc_height, e->foc.b_ceiling_height, 1);
	wjauge_set(d, e->rbr_quadrant.b_w, e->foc.b_x_size, 1);
	wjauge_set(d, e->rbr_quadrant.b_h, e->foc.b_y_size, 1);
}

void		select_block_type(t_doom *d, t_block_type *type)
{
	d->editor.selected_block = type;
	d->editor.foc.b_block_type = type->block_type;
	d->editor.foc.b_orientation = 0;
	d->editor.foc.b_x_size = 100;
	d->editor.foc.b_y_size = 100;
	d->editor.foc.b_height = 100;
	d->editor.foc.b_ceiling_height = 100;
	d->editor.foc.b_has_ceiling = 1;
	d->editor.foc.b_ceilng_tex = 1;
	d->editor.foc.b_floor_tex = 2;
	d->editor.foc.b_n_texture = 0;
	d->editor.foc.b_s_texture = 1;
	d->editor.foc.b_w_texture = 2;
	d->editor.foc.b_e_texture = 3;
	d->editor.foc.b_light = 0;
	d->editor.foc.b_collides = type->block_type == block_wall || type->block_type == block_small_wall ? 1 : 0;
	update_interactions(d);
}

void		copy_block_type(t_doom *d, t_block_type *type, t_mblock *blk)
{
	d->editor.selected_block = type;
	d->editor.foc.b_block_type = blk->block_type;
	d->editor.foc.b_orientation = blk->orientation;
	d->editor.foc.b_x_size = blk->x_size;
	d->editor.foc.b_y_size = blk->y_size;
	d->editor.foc.b_height = blk->height;
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
