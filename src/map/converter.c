/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 00:19:47 by cababou           #+#    #+#             */
/*   Updated: 2019/05/05 03:39:08 by cababou          ###   ########.fr       */
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
	nmap->size_x = map->width;
	nmap->size_y = map->height;
	nmap->skybox_color = make_rgb(0, 0, 0, 255);
	nmap->textures = lstcontainer_new();
	lstcontainer_add(nmap->textures, ft_lstget_fromelement(0, texs->firstelement)->content);
	lstcontainer_add(nmap->textures, ft_lstget_fromelement(1, texs->firstelement)->content);
	lstcontainer_add(nmap->textures, ft_lstget_fromelement(2, texs->firstelement)->content);
	lstcontainer_add(nmap->textures, ft_lstget_fromelement(3, texs->firstelement)->content);
	if(!(nmap->map = mmalloc(sizeof(t_mblock *) * nmap->size_y)))
		exit_program(doom, ERROR_SDL_AFTER_INIT);
	y = 0;
	while (y < nmap->size_y)
	{
		x = 0;
		nmap->map[y] = mmalloc(sizeof(t_mblock) * nmap->size_x);
		while (x < nmap->size_x)
		{
			nmap->map[y][x].block_type = char_to_blocktype(map->m[y][x]);
			nmap->map[y][x].orientation = 0;
			nmap->map[y][x].x_size = 100;
			nmap->map[y][x].y_size = 100;
			nmap->map[y][x].height = 100;
			nmap->map[y][x].ceiling_height = 100;
			nmap->map[y][x].has_ceiling = 1;
			nmap->map[y][x].ceilng_tex = 1;
			nmap->map[y][x].floor_tex = 2;
			nmap->map[y][x].n_texture = 0;
			nmap->map[y][x].s_texture = 1;
			nmap->map[y][x].w_texture = 2;
			nmap->map[y][x].e_texture = 3;
			nmap->map[y][x].light = 0xFFFFFFFF;
			nmap->map[y][x].has_ceiling = 1;
			nmap->map[y][x].collides = nmap->map[y][x].block_type == block_wall || nmap->map[y][x].block_type == block_small_wall ? 1 : 0;
			nmap->map[y][x].x = x;
			nmap->map[y][x].y = y;
			x++;
		}
		y++;
	}
	nmap->map[map->start_y][map->start_x].block_type = block_spawn;
	return (nmap);
}
