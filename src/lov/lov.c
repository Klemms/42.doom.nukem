/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 11:20:18 by hdussert          #+#    #+#             */
/*   Updated: 2019/05/01 02:14:41 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int					calc_column(t_sight *p, t_doom *doom, int num)
{
	double	col;
	SDL_Surface	*tmp = get_surface(doom, p->saw_that[num].tex);

	if (!tmp)
		return (0);
	if (p->saw_that[num].side == 1)
		col = p->saw_that[num].x + p->saw_that[num].z * p->ray_dir.x;
	else
		col = p->saw_that[num].y + p->saw_that[num].z * p->ray_dir.y;
	col = col - floor(col);
	col = round(col * (tmp->w - 1));
	if ((p->saw_that[num].side == 0 && p->ray_dir.x > 0)
	|| (p->saw_that[num].side == 1 && p->ray_dir.y < 0))
		col = tmp->w - col - 1;
	return (col);
}

double				calc_perp_dist(t_sight *p, t_player *you, int num)
{
	if (p->saw_that[num].side == 0)
		return(((int)p->saw_that[num].x - you->pos.x
			+ (1.0 - p->step.x) / 2.0) / p->ray_dir.x);
	else
		return(((int)p->saw_that[num].y - you->pos.y
			+ (1.0 - p->step.y) / 2.0) / p->ray_dir.y);
}

double				calc_perp_dist_next(t_sight *p, t_player *you, int num, int num2)
{
	if (num2 == 0)
		return(((int)p->saw_that[num].next_x - you->pos.x
			+ (1.0 - p->step.x) / 2.0) / p->ray_dir.x);
	else
		return(((int)p->saw_that[num].next_y - you->pos.y
			+ (1.0 - p->step.y) / 2.0) / p->ray_dir.y);
}

void				calc_lov(t_doom *doom)
{
	int		x;
	int		column;
	int		cptest;

	x = 0;
	while (x < doom->settings.window_width)
	{
		init_sight(doom, &doom->sight, x, &doom->you);
		if (see_wall(&doom->sight, doom))
		{
			cptest = doom->sight.queue_cpt;
			while (--cptest >= 0)
			{
				column = calc_column(&doom->sight, doom, cptest);
				draw_wall(doom, x, column, cptest);
			}
		}
		x++;
	}
}
