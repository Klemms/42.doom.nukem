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

void				draw_wall(t_wolf *w, double x, int column, int num)
{
	double	line_height;
	int		draw_start;
	int		draw_end;
	int		py;
	int		wall_size;


	line_height = (int)(w->w_height / w->sight->saw_that[num].z);
	if (w->map->m[(int)w->sight->saw_that[num].y][(int)w->sight->saw_that[num].x] == 'T')
	{
		draw_end = line_height / 2 + w->w_height / 2;
		draw_start = line_height / 6 + w->w_height / 2;
	}
	else
	{
		draw_start = -line_height / 2 + w->w_height / 2;
		draw_end = line_height / 2 + w->w_height / 2;
	}
	wall_size = draw_end - draw_start;
	py = draw_start;
	py = (py < 0 ? 0 : py);
	draw_end = (draw_end > w->w_height ? w->w_height - 1 : draw_end);
	if (w->sight->hit)
		while (py < draw_end)
		{
			line_height = (py - draw_start) / (double)wall_size;
			w->temp_color = ((int *)w->texture[w->sight->saw_that[num].tex].img.img)[column
				+ (int)round(line_height * (w->texture[w->sight->saw_that[num].tex].height - 1))
				* w->texture[w->sight->saw_that[num].tex].width];
			pixel_put(w, w->image->img, x, py);
			py++;
		}
	if (w->map->m[(int)w->sight->saw_that[num].y][(int)w->sight->saw_that[num].x] == 'T')
	{
		line_height = (int)(w->w_height / w->sight->saw_that[num].z);
		draw_end = line_height / 6 + w->w_height / 2;
		draw_end = (draw_end > w->w_height ? w->w_height - 1 : draw_end);
		line_height = (int)(w->w_height / w->sight->saw_that[num].next_perp);
		draw_start = (line_height / 6 + w->w_height / 2) - 1;
		while (++draw_start < draw_end)
			((int *)w->image->img)[(int)x + draw_start * w->w_width] = 0x6CAAC2;
	}
}

int					see_wall(t_sight *p, t_wolf *w)
{
	p->queue_cpt = 0;
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
		&& ((w->map->m[(int)p->pos->y][(int)p->pos->x] == '#') 
		|| (w->map->m[(int)p->pos->y][(int)p->pos->x] == 'T')))
		{
			p->saw_that[p->queue_cpt].x = p->pos->x;
			p->saw_that[p->queue_cpt].y = p->pos->y;
			p->saw_that[p->queue_cpt].side = p->side;
			p->saw_that[p->queue_cpt].z = calc_perp_dist(w->sight, w->you, p->queue_cpt);
			if (p->side == 1)
				p->saw_that[p->queue_cpt].tex = p->step.y < 0;
			else
				p->saw_that[p->queue_cpt].tex = (p->step.x < 0 ? 2 : 3);

			p->saw_that[p->queue_cpt].next_x = p->pos->x;
			p->saw_that[p->queue_cpt].next_y = p->pos->y;
			int tmpside;
			if (p->side_dist.x < p->side_dist.y)
			{
				p->saw_that[p->queue_cpt].next_x += p->step.x;
				tmpside = 0;
			}
			else
			{
				p->saw_that[p->queue_cpt].next_y = p->pos->y + p->step.y;
				tmpside = 1;
			}
			p->saw_that[p->queue_cpt].next_perp = calc_perp_dist_next(w->sight, w->you, p->queue_cpt, tmpside);
			p->queue_cpt++;
			if (w->map->m[(int)p->pos->y][(int)p->pos->x] == '#')
				break;
		}
		p->cpt += 1;
	}
	return (p->cpt < p->rov ? (p->hit = 1) : 0);
}
