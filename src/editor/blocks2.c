/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 09:57:18 by cababou           #+#    #+#             */
/*   Updated: 2019/05/06 10:02:08 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_mblock	*new_block(t_doom *d, int block_type, int x, int y)
{
	t_mblock	*b;

	if (!(b = mmalloc(sizeof(t_mblock))))
		exit_program(d, ERROR_SDL_AFTER_INIT);
	b->block_type = block_type;
	b->orientation = 0;
	b->x_size = 100;
	b->y_size = 100;
	b->height = 100;
	b->ceiling_height = 100;
	b->has_ceiling = 1;
	b->ceilng_tex = 1;
	b->floor_tex = 2;
	b->n_texture = 0;
	b->s_texture = 1;
	b->w_texture = 2;
	b->e_texture = 3;
	b->light = 0xFFFFFFFF;
	b->has_ceiling = 1;
	b->collides = b->block_type == block_wall || b->block_type == block_small_wall ? 1 : 0;
	b->x = x;
	b->y = y;
	return (b);
}
