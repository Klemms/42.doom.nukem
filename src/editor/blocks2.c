/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 09:57:18 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 23:49:36 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "editor.h"

void		apply_sprite_texture(t_doom *d, int texture_id)
{
	if (d->editor.texture_edited == 0)
		d->editor.foc_s.b_texture = texture_id;
	if (d->editor.texture_edited == 1)
		d->editor.foc_s.b_texture_back = texture_id;
	switch_tool_sprite(d, tool_sprite, d->editor.selected_sprite);
}

void		apply_block_texture(t_doom *d, int texture_id)
{
	if (d->editor.selected_sprite)
		apply_sprite_texture(d, texture_id);
	if (d->editor.selected_sprite)
		return ;
	if (d->editor.texture_edited == 0)
		d->editor.foc.b_n_texture = texture_id;
	else if (d->editor.texture_edited == 1)
		d->editor.foc.b_s_texture = texture_id;
	else if (d->editor.texture_edited == 2)
		d->editor.foc.b_w_texture = texture_id;
	else if (d->editor.texture_edited == 3)
		d->editor.foc.b_e_texture = texture_id;
	switch_tool(d, tool_block, d->editor.selected_block);
}

void		apply_block_settings(t_doom *d, t_mblock *dest)
{
	int	oldt;

	oldt = dest->block_type;
	dest->block_type = d->editor.foc.b_block_type;
	dest->orientation = d->editor.foc.b_orientation;
	dest->x_size = d->editor.foc.b_x_size;
	dest->y_size = d->editor.foc.b_y_size;
	dest->event_id = d->editor.foc.b_event_id;
	dest->ceiling_height = d->editor.foc.b_ceiling_height;
	dest->has_ceiling = d->editor.foc.b_has_ceiling;
	dest->ceilng_tex = d->editor.foc.b_ceilng_tex;
	dest->floor_tex = d->editor.foc.b_floor_tex;
	dest->n_texture = d->editor.foc.b_n_texture;
	dest->s_texture = d->editor.foc.b_s_texture;
	dest->w_texture = d->editor.foc.b_w_texture;
	dest->e_texture = d->editor.foc.b_e_texture;
	dest->light = d->editor.foc.b_light;
	dest->collides = d->editor.foc.b_block_type == block_wall
		|| d->editor.foc.b_block_type == block_door
		|| d->editor.foc.b_block_type == block_window
		|| d->editor.foc.b_block_type == block_button ? 1 : 0;
	blockwindowdoor_removed(d, oldt, dest->x, dest->y);
	blockwindowdoor_added(d, dest);
}

void		init_bloc(t_mblock *b)
{
	b->floor_tex = 0;
	b->n_texture = 0;
	b->s_texture = 0;
	b->w_texture = 0;
	b->e_texture = 0;
}

t_mblock	*new_block(t_doom *d, int block_type, int x, int y)
{
	t_mblock	*b;

	if (!(b = mmalloc(sizeof(t_mblock))))
		exit_program(d, ERROR_SDL_AFTER_INIT);
	b->block_type = block_type;
	b->orientation = 0;
	b->x_size = 100;
	b->y_size = 100;
	b->event_id = 0;
	b->ceiling_height = 100;
	b->has_ceiling = 1;
	b->ceilng_tex = 0;
	init_bloc(b);
	b->light = 0xFFFFFFFF;
	b->has_ceiling = 1;
	b->collides = b->block_type == block_wall
		|| b->block_type == block_door
		|| b->block_type == block_window
		|| b->block_type == block_button ? 1 : 0;
	b->x = x;
	b->y = y;
	return (b);
}
