/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 11:20:18 by hdussert          #+#    #+#             */
/*   Updated: 2019/04/05 14:20:26 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf3d.h"

int					calc_column(t_sight *p, t_wolf *w, int tex)
{
	double	col;

	if (p->side == 1)
		col = p->pos->x + p->perp_wall_dist * p->ray_dir.x;
	else
		col = p->pos->y + p->perp_wall_dist * p->ray_dir.y;
	col = col - floor(col);
	col = round(col * (double)(w->texture[tex].width - 1));
	if ((p->side == 0 && p->ray_dir.x > 0)
	|| (p->side == 1 && p->ray_dir.y < 0))
		col = w->texture[tex].width - col - 1;
	return (col);
}

void				calc_perp_dist(t_sight *p, t_player *you)
{
	if (p->side == 0)
		p->perp_wall_dist = ((int)p->pos->x - you->pos->x
			+ (1.0 - p->step.x) / 2.0) / p->ray_dir.x;
	else
		p->perp_wall_dist = ((int)p->pos->y - you->pos->y
			+ (1.0 - p->step.y) / 2.0) / p->ray_dir.y;
}

void				calc_lov(t_wolf *w)
{
	int		x;
	int		column;
	int		tex;

	x = 0;
	while (x < w->w_width)
	{
		init_sight(w, x, w->you);
		if (see_wall(w->sight, w))
		{
			if (w->sight->side == 1)
				tex = w->sight->step.y < 0;
			else
				tex = (w->sight->step.x < 0 ? 2 : 3);
			column = calc_column(w->sight, w, tex);
			draw_wall(w, x, column, tex);
		}
		x++;
		ffree(w->sight->pos);
		w->sight->pos = NULL;
	}
}
