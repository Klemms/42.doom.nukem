/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdussert <hdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 01:01:55 by hdussert          #+#    #+#             */
/*   Updated: 2019/05/08 01:03:34 by hdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		sprite_rayhit2(t_raycasting *rc)
{
	if (rc->side_dist.x < rc->side_dist.y)
	{
		rc->side_dist.x += rc->delta_dist.x;
		rc->map.x += rc->step.x;
		rc->side = 0;
	}
	else
	{
		rc->side_dist.y += rc->delta_dist.y;
		rc->map.y += rc->step.y;
		rc->side = 1;
	}
}

int			sprite_rayhit(t_raycasting *rc, t_player *p, t_nmap *nmap)
{
	int hit;

	(void)p;
	hit = 0;
	rc->dist_hit = 0;
	while (hit == 0 && rc->dist_hit < 40)
	{
		sprite_rayhit2(rc);
		rc->dist_hit++;
		if (nmap->map[rc->map.y][rc->map.x].collides
		|| nmap->map[rc->map.y][rc->map.x].block_type == block_door)
		{
			if (nmap->map[rc->map.y][rc->map.x].block_type == block_window
			|| nmap->map[rc->map.y][rc->map.x].block_type == block_door)
				return (1);
			else
				return (0);
		}
	}
	return (0);
}
