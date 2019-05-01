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
	t_wall_sight	*queue;
	t_draw_wall 	d;

	queue = doom->sight.queue;
	SDL_Surface	*tmp;

	tmp = get_surface(doom, queue[num].tex);
	d.line_height = (int)(WIN_HEIGHT / queue[num].z);
	if (doom->map.m[(int)queue[num].y][(int)queue[num].x] == 'T')
	{
		d.end = d.line_height / 2 + WIN_HEIGHT / 2;
		d.start = d.line_height / 6 + WIN_HEIGHT / 2;
	}
	else
	{
		d.start = -d.line_height / 2 + WIN_HEIGHT / 2;
		d.end = d.line_height / 2 + WIN_HEIGHT / 2;
	}
	// TEXTURE FLOOR
	int my_s = d.end;
	int	my_e = WIN_HEIGHT - 1;
	while (++my_s < my_e)
	{
		int		c = rand();
		pixel_put(doom, x, my_s, (c % 2 ? 0xFFFFFF : 0x000000));
	}
	// -------------
	d.wall_size = d.end - d.start;
	d.py = d.start;
	d.py = (d.py < 0 ? 0 : d.py);
	d.end = (d.end > WIN_HEIGHT ? WIN_HEIGHT - 1 : d.end);
	if (doom->sight.hit)
		while (d.py < d.end)
		{
			d.line_height = (d.py - d.start) / (double)(d.wall_size);
			doom->temp_color = doom->settings.default_wall_color;
			if (!tmp || !doom->settings.render_textures)
				doom->temp_color = doom->settings.default_wall_color;
			else
				doom->temp_color = ((Uint32 *)tmp->pixels)[column
					+ (int)(d.line_height * (tmp->h - 1))
					* tmp->w];
			pixel_put(doom, x, d.py, doom->temp_color);
			d.py++;
		}
	if (doom->map.m[(int)queue[num].y][(int)queue[num].x] == 'T')
	{
		d.line_height = (int)(WIN_HEIGHT / queue[num].z);
		d.end = d.line_height / 6.0 + WIN_HEIGHT / 2.0;
		d.end = (d.end > WIN_HEIGHT ? WIN_HEIGHT - 1 : d.end);
		d.line_height = (int)(WIN_HEIGHT / queue[num].next_perp);
		d.start = (d.line_height / 6.0 + WIN_HEIGHT / 2.0) - 1;
		while (++d.start < d.end)
			((Uint32 *)doom->surface->pixels)[(int)x + d.start * WIN_WIDTH] = doom->settings.default_wall_color;
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
