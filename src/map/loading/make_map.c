/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 21:06:51 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 22:37:48 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		make_map(t_doom *d, t_nmap *m)
{
	if (d->game_mode == M_GAME)
		exit_program(d, ERROR_INVALID_MAP);
	if (!(m->map = mmalloc(sizeof(t_mblock *)))
		|| !(m->map[0] = mmalloc(sizeof(t_mblock))))
		exit_program(d, ERROR_SDL_AFTER_INIT);
	d->nmap = m;
	m->map[0][0].block_type = block_wall;
	m->map[0][0].collides = 1;
	m->map[0][0].n_texture = 0;
	m->map[0][0].s_texture = 0;
	m->map[0][0].w_texture = 0;
	m->map[0][0].e_texture = 0;
	m->map[0][0].floor_tex = 0;
	m->map[0][0].ceilng_tex = 1;
	m->map[0][0].x = 0;
	m->map[0][0].y = 0;
	m->size_x = 1;
	m->size_y = 1;
	m->sprites = lstcontainer_new();
	m->spritecount = 0;
	m->textures = lstcontainer_new();
	add_texture(d, "helene.xpm");
	add_texture(d, "nicolas.xpm");
	if (lstcontainer_size(d->nmap->textures) <= 0)
		exit_program(d, ERROR_MAP_MISSING_TEXTURES);
}
