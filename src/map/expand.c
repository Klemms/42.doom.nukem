/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 09:23:38 by cababou           #+#    #+#             */
/*   Updated: 2019/05/06 11:10:27 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	copy_old_map(t_doom *d, t_mblock **old, t_nmap *m, SDL_Rect sz)
{
	size_t	x;
	size_t	y;

	if (!(m->map = mmalloc(sizeof(t_mblock *) * m->size_y)))
		exit_program(d, ERROR_SDL_AFTER_INIT);
	y = 0;
	while (y < sz.y)
	{
		if (!(m->map[y] = mmalloc(sizeof(t_mblock) * m->size_x)))
			exit_program(d, ERROR_SDL_AFTER_INIT);
		x = 0;
		while (x < sz.x)
		{
			copy_block(&m->map[y][x], &old[y][x], 0, 1);
			x++;
		}
		y++;
	}
}

void	free_old_map(t_mblock **old, size_t y_size)
{
	size_t		x;
	size_t		y;

	y = 0;
	while (y < y_size)
	{
		free(old[y]);
		y++;
	}
	free(old);
	old = NULL;
}

void	expand_map2(t_doom *d, t_nmap *m, SDL_Rect old_sz, t_mblock *b)
{
	size_t		x;
	size_t		y;

	y = 0;
	while (y < m->size_y)
	{
		if (y > old_sz.y - 1
			&& !(m->map[y] = mmalloc(sizeof(t_mblock) * m->size_x)))
			exit_program(d, ERROR_SDL_AFTER_INIT);
		x = 0;
		while (x < m->size_x)
		{
			if (x >= old_sz.x || y >= old_sz.y)
			{
				if (b->x == x && b->y == y)
					copy_block(&m->map[y][x], b, 0, 1);
				else
					set_to_default_mblock(&m->map[y][x], x, y);
			}
			x++;
		}
		y++;
	}
}

void	expand_map(t_doom *d, t_nmap *m, t_mblock *b)
{
	t_mblock	**old_m;
	SDL_Rect	old_sz;

	old_m = m->map;
	old_sz = make_rect(m->size_x, m->size_y, 0, 0);
	m->size_x = b->x > m->size_x - 1 ? b->x + 1 : m->size_x;
	m->size_y = b->y > m->size_y - 1 ? b->y + 1 : m->size_y;
	copy_old_map(d, old_m, m, old_sz);
	expand_map2(d, m, old_sz, b);
	free_old_map(old_m, old_sz.y);
	free(b);
}
