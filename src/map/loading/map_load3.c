/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 11:57:34 by cababou           #+#    #+#             */
/*   Updated: 2019/05/05 12:19:43 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	read_texture(t_doom *d, t_nmap *m, char *l)
{
	SDL_Surface	*s;
	size_t		sz;
	int			size_x;
	int			size_y;
	int			gnc;

	if (l[0] == '[')
	{
		ft_putendl("LOADING TEXTURE");
		gnc = ft_getnextchar(l, ',');
		size_x = ft_atoi(l + 1);
		l = ft_strsub(l, gnc, ft_strlen(l) - gnc, 1);
		gnc = ft_getnextchar(l, ',');
		size_y = ft_atoi(l);
		l = ft_strsub(l, gnc, ft_strlen(l) - gnc, 1);
		sz = 0;
		s = SDL_CreateRGBSurfaceWithFormat(0, size_x, size_y, 32, d->surface->format->format);
		while (sz < size_x * size_y)
		{
			gnc = ft_getnextchar(l, ',');
			((Uint32 *)s->pixels)[sz] = ft_atoi(l + gnc);
			sz++;
		}
		lstcontainer_add(m->textures, make_texture(d, s, NULL));
	}
}
