/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sight.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 03:30:59 by cababou           #+#    #+#             */
/*   Updated: 2019/04/29 21:52:39 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_sight(t_doom *doom, double x, t_player *you)
{
	t_sight *p;

	p = doom->sight;
	p->camera_x = 2.0 * x / (double)(doom->settings->window_width) - 1.0;
	p->ray_dir.x = you->dir->x + you->plane->x * p->camera_x;
	p->ray_dir.y = you->dir->y + you->plane->y * p->camera_x;
	p->step.x = (p->ray_dir.x < 0 ? -1 : 1);
	p->step.y = (p->ray_dir.y < 0 ? -1 : 1);
	p->pos = new_vec(you->pos->x, you->pos->y, 0);
	p->rov = you->rov;
	p->delta_dist.x = fabs(1 / p->ray_dir.x);
	p->delta_dist.y = fabs(1 / p->ray_dir.y);
	p->side_dist.x = (p->ray_dir.x < 0 ?
					(you->pos->x - (int)p->pos->x) * p->delta_dist.x :
					((int)p->pos->x + 1.0 - you->pos->x) * p->delta_dist.x);
	p->side_dist.y = (p->ray_dir.y < 0 ?
					(you->pos->y - (int)p->pos->y) * p->delta_dist.y :
					((int)p->pos->y + 1.0 - you->pos->y) * p->delta_dist.y);
}
