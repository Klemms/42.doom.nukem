/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfc_init2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 23:51:35 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 23:52:55 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	wfc_init2(t_raycasting *rc, t_player *p)
{
	if (rc->ray_dir.x < 0)
	{
		rc->step.x = -1;
		rc->side_dist.x = (p->pos.x - rc->map.x) * rc->delta_dist.x;
	}
	else
	{
		rc->step.x = 1;
		rc->side_dist.x = (rc->map.x + 1.0 - p->pos.x) * rc->delta_dist.x;
	}
	if (rc->ray_dir.y < 0)
	{
		rc->step.y = -1;
		rc->side_dist.y = (p->pos.y - rc->map.y) * rc->delta_dist.y;
	}
	else
	{
		rc->step.y = 1;
		rc->side_dist.y = (rc->map.y + 1.0 - p->pos.y) * rc->delta_dist.y;
	}
}

void	wfc_init(t_raycasting *rc, t_player *p)
{
	rc->p_z = p->pitch;
	rc->camera_x = 2 * rc->x / (double)(WIN_W) - 1;
	rc->ray_dir.x = p->dir.x + p->plane.x * rc->camera_x;
	rc->ray_dir.y = p->dir.y + p->plane.y * rc->camera_x;
	rc->map.x = (int)(p->pos.x);
	rc->map.y = (int)(p->pos.y);
	rc->delta_dist.x = fabs(1 / rc->ray_dir.x);
	rc->delta_dist.y = fabs(1 / rc->ray_dir.y);
	wfc_init2(rc, p);
}
