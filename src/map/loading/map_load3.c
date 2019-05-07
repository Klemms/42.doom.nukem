/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 11:57:34 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 20:53:06 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		mgnc(char *str, char c)
{
	return (ft_getnextchar(str, c));
}

void	read_texture(t_doom *d, t_nmap *m, char *l)
{
	SDL_Surface	*s;
	size_t		sz;
	int			size_x;
	int			size_y;
	int			gnc;

	if (l[0] == '[')
	{
		size_x = ft_atoi(l + 1, 0);
		l = ft_strsub(l, mgnc(l, ','), ft_strlen(l) - mgnc(l, ','), 1);
		size_y = ft_atoi(l, 0);
		l = ft_strsub(l, mgnc(l, ','), ft_strlen(l) - mgnc(l, ','), 1);
		sz = 0;
		s = SDL_CreateRGBSurfaceWithFormat(0, size_x, size_y, 32,
			d->surface->format->format);
		gnc = 0;
		while (sz < (size_t)size_x * (size_t)size_y)
		{
			((Uint32 *)s->pixels)[sz] = ft_atoi(l + gnc, 0);
			gnc += mgnc(l + gnc, ',');
			sz++;
		}
		lstcontainer_add(m->textures, make_texture(d, s, NULL));
		free(l);
	}
}
