/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:58:00 by cababou           #+#    #+#             */
/*   Updated: 2019/05/01 02:18:03 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

Uint32				get_texture_pixel(t_texture *texture, int x, int y)
{
	SDL_Surface	*surf;

	if (!texture || !texture->surface)
		return (-1);
	surf = texture->surface;
	return (get_t_exact_pixel(texture, x % surf->w, y % surf->h));
}

void				draw_wall(t_doom *doom, double x, int column, int num)
{
	double		line_height;
	int			draw_start;
	int			draw_end;
	int			py;
	int			wall_size;
	SDL_Surface	*tmp;

	tmp = get_surface(doom, doom->sight.queue[num].tex);
	line_height = (int)(doom->settings.window_height / doom->sight.queue[num].z);
	if (doom->map.m[(int)doom->sight.queue[num].y][(int)doom->sight.queue[num].x] == 'T')
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
			if (!tmp || !doom->settings.render_textures)
				doom->temp_color = doom->settings.default_wall_color;
			else
				doom->temp_color = ((Uint32 *)tmp->pixels)[column
					+ (int)(line_height * (tmp->h - 1))
					* tmp->w];
			pixel_put(doom, x, py, doom->temp_color);
			py++;
		}
	if (doom->map.m[(int)doom->sight.queue[num].y][(int)doom->sight.queue[num].x] == 'T')
	{
		line_height = (int)(doom->settings.window_height / doom->sight.queue[num].z);
		draw_end = line_height / 6.0 + doom->settings.window_height / 2.0;
		draw_end = (draw_end > doom->settings.window_height ? doom->settings.window_height - 1 : draw_end);
		line_height = (int)(doom->settings.window_height / doom->sight.queue[num].next_perp);
		draw_start = (line_height / 6.0 + doom->settings.window_height / 2.0) - 1;
		while (++draw_start < draw_end)
			((Uint32 *)doom->surface->pixels)[(int)x + draw_start * doom->settings.window_width] = doom->settings.default_wall_color;
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
			p->queue[p->queue_cpt].x = p->pos.x;
			p->queue[p->queue_cpt].y = p->pos.y;
			p->queue[p->queue_cpt].side = p->side;
			p->queue[p->queue_cpt].z = calc_perp_dist(&doom->sight, &doom->you, p->queue_cpt);
			if (p->side == 1)
				p->queue[p->queue_cpt].tex = p->step.y < 0;
			else
				p->queue[p->queue_cpt].tex = (p->step.x < 0 ? 2 : 3);

			int tmpside;
			if (p->side_dist.x < p->side_dist.y)
			{
				p->queue[p->queue_cpt].next_x = p->pos.x + p->step.x;
				p->queue[p->queue_cpt].next_y = p->pos.y;
				tmpside = 0;
			}
			else
			{
				p->queue[p->queue_cpt].next_x = p->pos.x;
				p->queue[p->queue_cpt].next_y = p->pos.y + p->step.y;
				tmpside = 1;
			}
			p->queue[p->queue_cpt].next_perp = calc_perp_dist_next(&doom->sight, &doom->you, p->queue_cpt, tmpside);
			p->queue_cpt++;
			if (doom->map.m[(int)p->pos.y][(int)p->pos.x] == '#')
				break;
		}
		p->cpt += 1;
	}
	return (p->cpt < p->rov ? (p->hit = 1) : 0);
}
