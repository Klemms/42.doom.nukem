/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:58:00 by cababou           #+#    #+#             */
/*   Updated: 2019/04/30 20:07:54 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void				draw_wall(t_doom *doom, double x, int column, int num)
{
	double	line_height;
	int		draw_start;
	int		draw_end;
	int		py;
	int		wall_size;


	line_height = (int)(doom->settings.window_height / doom->sight.saw_that[num].z);
	if (doom->map.m[(int)doom->sight.saw_that[num].y][(int)doom->sight.saw_that[num].x] == 'T')
	{
		draw_end = line_height / 2 + doom->settings.window_height / 2;
		draw_start = line_height / 6 + doom->settings.window_height / 2;
	}
	else
	{
		draw_start = -line_height / 2 + doom->settings.window_height / 2;
		draw_end = line_height / 2 + doom->settings.window_height / 2;
	}
	wall_size = draw_end - draw_start;
	py = draw_start;
	py = (py < 0 ? 0 : py);
	draw_end = (draw_end > doom->settings.window_height ? doom->settings.window_height - 1 : draw_end);
	if (doom->sight.hit)
		while (py < draw_end)
		{
			line_height = (py - draw_start) / (double)wall_size;
			doom->temp_color = doom->settings.default_wall_color;
			/*doom->temp_color = ((int *)doom->texture[tex].img.img)[column
				+ (int)round(line_height * (doom->texture[tex].height - 1))
				* doom->texture[tex].width];*/
			pixel_put(doom, x, py, doom->temp_color);
			py++;
		}
	if (doom->map.m[(int)doom->sight.saw_that[num].y][(int)doom->sight.saw_that[num].x] == 'T')
	{
		line_height = (int)(doom->settings.window_height / doom->sight.saw_that[num].z);
		draw_end = line_height / 6 + doom->settings.window_height / 2;
		draw_end = (draw_end > doom->settings.window_height ? doom->settings.window_height - 1 : draw_end);
		line_height = (int)(doom->settings.window_height / doom->sight.saw_that[num].next_perp);
		draw_start = (line_height / 6 + doom->settings.window_height / 2) - 1;
		while (++draw_start < draw_end)
			((Uint32 *)doom->surface->pixels)[(int)x + draw_start * doom->settings.window_width] = 0x6CAAC2;
	}
}

int					see_wall(t_sight *p, t_doom *doom)
{
	p->queue_cpt = 0;
	p->hit = 0;
	p->cpt = 0;
	while (p->hit == 0 && p->cpt < p->rov)
	{
		if (p->side_dist.x < p->side_dist.y)
		{
			p->side_dist.x += p->delta_dist.x;
			p->pos.x += p->step.x;
			p->side = 0;
		}
		else
		{
			p->side_dist.y += p->delta_dist.y;
			p->pos.y += p->step.y;
			p->side = 1;
		}

		if (p->pos.x >= 0 && p->pos.x < doom->map.width
		&& p->pos.y >= 0 && p->pos.y < doom->map.height
		&& ((doom->map.m[(int)p->pos.y][(int)p->pos.x] == '#') 
		|| (doom->map.m[(int)p->pos.y][(int)p->pos.x] == 'T')))
		{
			p->saw_that[p->queue_cpt].x = p->pos.x;
			p->saw_that[p->queue_cpt].y = p->pos.y;
			p->saw_that[p->queue_cpt].side = p->side;
			p->saw_that[p->queue_cpt].z = calc_perp_dist(&doom->sight, &doom->you, p->queue_cpt);
			if (p->side == 1)
				p->saw_that[p->queue_cpt].tex = p->step.y < 0;
			else
				p->saw_that[p->queue_cpt].tex = (p->step.x < 0 ? 2 : 3);

			p->saw_that[p->queue_cpt].next_x = p->pos.x;
			p->saw_that[p->queue_cpt].next_y = p->pos.y;
			int tmpside;
			if (p->side_dist.x < p->side_dist.y)
			{
				p->saw_that[p->queue_cpt].next_x += p->step.x;
				tmpside = 0;
			}
			else
			{
				p->saw_that[p->queue_cpt].next_y = p->pos.y + p->step.y;
				tmpside = 1;
			}
			p->saw_that[p->queue_cpt].next_perp = calc_perp_dist_next(&doom->sight, &doom->you, p->queue_cpt, tmpside);
			p->queue_cpt++;
			if (doom->map.m[(int)p->pos.y][(int)p->pos.x] == '#')
				break;
		}
		p->cpt += 1;
	}
	return (p->cpt < p->rov ? (p->hit = 1) : 0);
}
