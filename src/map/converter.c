/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 00:19:47 by cababou           #+#    #+#             */
/*   Updated: 2019/05/04 02:13:03 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_nmap	*convert_map(t_doom *doom, t_map *map, t_lstcontainer *texs)
{
	t_nmap	*nmap;
	int		x;
	int		y;

	if (!doom || !map || !texs || lstcontainer_size(texs) < 4)
		return (NULL);
	if (!(nmap = mmalloc(sizeof(t_nmap))))
		exit_program(doom, ERROR_SDL_AFTER_INIT);
	nmap->map_name = ft_strdup(map->map_name);
	nmap->size_x = map->height;
	nmap->size_y = map->width;
	nmap->skybox_color = make_rgb(0, 0, 0, 255);
	nmap->textures = lstcontainer_new();
	lstcontainer_add(nmap->textures, ft_lstget_fromelement(0, texs->firstelement));
	lstcontainer_add(nmap->textures, ft_lstget_fromelement(1, texs->firstelement));
	lstcontainer_add(nmap->textures, ft_lstget_fromelement(2, texs->firstelement));
	lstcontainer_add(nmap->textures, ft_lstget_fromelement(3, texs->firstelement));
	if(!(nmap->map = mmalloc(sizeof(t_mblock *) * nmap->size_x)))
		exit_program(doom, ERROR_SDL_AFTER_INIT);
	x = 0;
	while (x < nmap->size_x)
	{
		y = 0;
		nmap->map[x] = mmalloc(sizeof(t_mblock) * nmap->size_y);
		while (y < nmap->size_y)
		{
			nmap->map[x][y].block_type = char_to_blocktype(map->m[x][y]);
			nmap->map[x][y].n_texture = 0;
			nmap->map[x][y].s_texture = 1;
			nmap->map[x][y].w_texture = 2;
			nmap->map[x][y].e_texture = 3;
			nmap->map[x][y].orientation = 0;
			nmap->map[x][y].height = 100;
			nmap->map[x][y].x_size = 100;
			nmap->map[x][y].y_size = 100;
			nmap->map[x][y].light = 0xFFFFFFFF;
			nmap->map[x][y].ceiling_height = 100;
			nmap->map[x][y].ceilng_tex = 0;
			nmap->map[x][y].has_ceiling = 1;
			nmap->map[x][y].has_ceiling = 1;
			nmap->map[x][y].floor_tex = 2;
			nmap->map[x][y].floor_tex = nmap->map[x][y].block_type == block_wall || nmap->map[x][y].block_type == block_small_wall ? 1 : 0;
			nmap->map[x][y].x = x;
			nmap->map[x][y].x = y;
			y++;
		}
		x++;
	}
	return (nmap);
}
