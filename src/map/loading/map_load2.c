/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 07:25:25 by cababou           #+#    #+#             */
/*   Updated: 2019/05/05 13:20:28 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
		b->block_type = i == 0 ? ft_atoi(l) : b->block_type;
		b->orientation = i == 0 ? ft_atoi(l) : b->orientation;
		b->x_size = i == 0 ? ft_atoi(l) : b->x_size;
		b->y_size = i == 0 ? ft_atoi(l) : b->y_size;
		b->height = i == 0 ? ft_atoi(l) : b->height;
		b->ceiling_height = i == 0 ? ft_atoi(l) : b->ceiling_height;
		b->has_ceiling = i == 0 ? ft_atoi(l) : b->has_ceiling;
		b->ceilng_tex = i == 0 ? ft_atoi(l) : b->ceilng_tex;
		b->floor_tex = i == 0 ? ft_atoi(l) : b->floor_tex;
		b->n_texture = i == 0 ? ft_atoi(l) : b->n_texture;
		b->s_texture = i == 0 ? ft_atoi(l) : b->s_texture;
		b->w_texture = i == 0 ? ft_atoi(l) : b->w_texture;
		b->e_texture = i == 0 ? ft_atoi(l) : b->e_texture;
		b->light = i == 0 ? ft_atoi(l) : b->light;
		b->collides = i == 0 ? ft_atoi(l) : b->collides;
		l = ft_strsub(l, gnc, ft_strlen(l) - gnc, 1);
		i++;
	}
	return (b);
}

void	read_blockline(t_doom *d, t_nmap *m, int y, char *l)
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
			if (x == 24)
			{
				;
			}
			block = ft_strsubuntilchar(l, 1, ']', 0);
			l = ft_strsub(l, ft_getnextchar(l + 1, '['), ft_strlen(l) - ft_getnextchar(l + 1, '['), 1);
			copy_block(&m->map[y][x], read_block(d, block), 1);
			m->map[y][x].x = x;
			m->map[y][x].y = y;
			x++;
			continue ;
		}
		else
			exit_program(d, ERROR_INVALID_MAP);
	}
}
