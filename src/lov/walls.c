/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:58:00 by cababou           #+#    #+#             */
/*   Updated: 2019/03/13 14:02:04 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf3d.h"

void				draw_wall(t_wolf *w, double x, int column, int tex)
{
	double	line_height;
	int		draw_start;
	int		draw_end;
	int		py;
	int		wall_size;

	calc_perp_dist(w->sight, w->you);
	line_height = (int)(w->w_height / w->sight->perp_wall_dist);
	draw_start = -line_height / 2 + w->w_height / 2;
	draw_end = line_height / 2 + w->w_height / 2;
	wall_size = draw_end - draw_start;
	py = draw_start;
	py = (py < 0 ? 0 : py);
	draw_end = (draw_end > w->w_height ? w->w_height - 1 : draw_end);
	if (w->sight->hit)
		while (py < draw_end)
		{
			line_height = (py - draw_start) / (double)wall_size;
			w->temp_color = ((int *)w->texture[tex].img.img)[column
				+ (int)round(line_height * (w->texture[tex].height - 1))
				* w->texture[tex].width];
			pixel_put(w, w->image->img, x, py);
			py++;
		}
}

int					see_wall(t_sight *p, t_wolf *w)
{
	p->hit = 0;
	p->cpt = 0;
	while (p->hit == 0 && p->cpt < p->rov)
	{
		if (p->side_dist.x < p->side_dist.y)
		{
			p->side_dist.x += p->delta_dist.x;
			p->pos->x += p->step.x;
			p->side = 0;
		}
		else
		{
			p->side_dist.y += p->delta_dist.y;
			p->pos->y += p->step.y;
			p->side = 1;
		}
		if (p->pos->x >= 0 && p->pos->x < w->map->width
		&& p->pos->y >= 0 && p->pos->y < w->map->height
		&& w->map->m[(int)p->pos->y][(int)p->pos->x] == '#')
			break ;
		p->cpt += 1;
	}
	return (p->cpt < p->rov ? (p->hit = 1) : 0);
}
