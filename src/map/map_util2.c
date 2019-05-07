/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_util2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 00:20:37 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 20:52:02 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

char		*map_reason_to_txt(int reason)
{
	if (reason == map_good)
		return ("Valid map");
	else if (reason == map_wall_contour)
		return ("Maps must be surrounded by walls");
	else if (reason == map_spawn_point)
		return ("Maps must have one spawn point");
	else if (reason == map_end_point)
		return ("Maps must have at least one end point");
	return ("Invalid map (Unknown reason)");
}

int			player_valid_tile(t_player *pl, t_nmap *nmap)
{
	t_mblock m;

	if (pl->pos.x < nmap->size_x && pl->pos.y < nmap->size_y)
	{
		m = nmap->map[(int)pl->pos.y][(int)pl->pos.x];
		if (nmap->map[(int)pl->pos.y][(int)pl->pos.x].collides)
			return (0);
		return (1);
	}
	return (0);
}

t_mblock	*get_spawn_point(t_nmap *nmap)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < (size_t)nmap->size_y)
	{
		x = 0;
		while (x < (size_t)nmap->size_x)
		{
			if (nmap->map[y][x].block_type == block_spawn)
				return (&nmap->map[y][x]);
			x++;
		}
		y++;
	}
	return (NULL);
}
