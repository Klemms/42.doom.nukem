/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 07:25:25 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 18:48:26 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		ml_setblocks(t_mblock *b, int i, char *l)
{
	b->block_type = i == 0 ? ft_atoi(l, 0) : b->block_type;
	b->orientation = i == 1 ? ft_atoi(l, 0) : b->orientation;
	b->x_size = i == 2 ? ft_atoi(l, 0) : b->x_size;
	b->y_size = i == 3 ? ft_atoi(l, 0) : b->y_size;
	b->event_id = i == 4 ? ft_atoi(l, 0) : b->event_id;
	b->ceiling_height = i == 5 ? ft_atoi(l, 0) : b->ceiling_height;
	b->has_ceiling = i == 6 ? ft_atoi(l, 0) : b->has_ceiling;
	b->ceilng_tex = i == 7 ? ft_atoi(l, 0) : b->ceilng_tex;
	b->floor_tex = i == 8 ? ft_atoi(l, 0) : b->floor_tex;
	b->n_texture = i == 9 ? ft_atoi(l, 0) : b->n_texture;
	b->s_texture = i == 10 ? ft_atoi(l, 0) : b->s_texture;
	b->w_texture = i == 11 ? ft_atoi(l, 0) : b->w_texture;
	b->e_texture = i == 12 ? ft_atoi(l, 0) : b->e_texture;
	b->light = i == 13 ? ft_atoi(l, 0) : b->light;
	b->collides = i == 14 ? ft_atoi(l, 0) : b->collides;
}

t_mblock	*read_block(t_doom *d, char *l)
{
	t_mblock	*b;
	int			i;
	int			gnc;

	if (!(b = mmalloc(sizeof(t_mblock))))
		exit_program(d, ERROR_INVALID_MAP);
	i = 0;
	while (l[0])
	{
		gnc = ft_getnextchar(l, ',');
		ml_setblocks(b, i, l);
		if (gnc < 0)
			break ;
		l = ft_strsub(l, gnc, ft_strlen(l) - gnc, 1);
		i++;
	}
	free(l);
	return (b);
}

void		read_blockline(t_doom *d, t_nmap *m, int y, char *l)
{
	int		x;
	char	*block;

	if (!(m->map[y] = mmalloc(sizeof(t_mblock) * m->size_x)))
		exit_program(d, ERROR_SDL_AFTER_INIT);
	x = 0;
	while (l[0])
	{
		if (l[0] == '[')
		{
			block = ft_strsubuntilchar(l, 1, ']', 0);
			l = ft_strsubuntil(l, ft_getnextchar(l + 1, '['), ft_strlen(l), 1);
			copy_block(&m->map[y][x], read_block(d, block), 1, 0);
			m->map[y][x].x = x;
			m->map[y][x].y = y;
			x++;
			continue ;
		}
		else
			exit_program(d, ERROR_INVALID_MAP);
	}
	free(l);
	l = NULL;
}
