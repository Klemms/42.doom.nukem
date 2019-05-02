/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:58:00 by cababou           #+#    #+#             */
/*   Updated: 2019/05/01 23:02:34 by cababou          ###   ########.fr       */
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

void				draw_wall(t_doom *doom, double x, double column, int num)
{
	t_wall_sight	*queue;
	t_draw_wall 	d;

	queue = doom->sight.queue;
	SDL_Surface	*tmp;

	tmp = get_surface(doom, queue[num].tex);
	d.line_height = (int)(doom->h / queue[num].z);
	// if (doom->map.m[(int)queue[num].y][(int)queue[num].x] == 'T')
	// {
	// 	doom->sight.end = d.line_height / 2 + doom->h / 2;
	// 	d.start = d.line_height / 6 + doom->h / 2;
	// }
	// else
	// {
	column = calc_column(&doom->sight, doom, 0);
	d.start = -d.line_height / 2.0 + doom->h / 2.0;
	doom->sight.end = d.line_height / 2.0 + doom->h / 2.0;
	// }
	
	d.wall_size = doom->sight.end - d.start;
	doom->sight.end = (doom->sight.end > doom->h ? doom->h - 1 : doom->sight.end);
	d.py = d.start;
	d.py = (d.py < 0 ? 0 : d.py);
	// if (doom->map.m[(int)queue[num].y][(int)queue[num].x] == 'T')
	// {
	// 	d.line_height = (int)(doom->h / queue[num].z);
	// 	doom->sight.end = d.line_height / 6.0 + doom->h / 2.0;
	// 	doom->sight.end = (doom->sight.end > doom->h ? doom->h - 1 : doom->sight.end);
	// 	d.line_height = (int)(doom->h / queue[num].next_perp);
	// 	d.start = (d.line_height / 6.0 + doom->h / 2.0) - 1;
	// 	while (++d.start < doom->sight.end)
	// 		doom->s_pixels[(int)x + d.start * doom->w] = doom->settings.default_wall_color;
	// }
	// if (doom->sight.hit)
		while (d.py < doom->sight.end)
		{
			d.line_height = (d.py - d.start) / (double)(d.wall_size);
			doom->temp_color = doom->settings.default_wall_color;
			if (!tmp || !doom->settings.render_textures)
				doom->temp_color = doom->settings.default_wall_color;
			else
				doom->temp_color = ((Uint32 *)tmp->pixels)[(int)column
					+ (int)(d.line_height * (tmp->h - 1))
					* tmp->w];
			if (doom->sight.queue[0].side == 1) doom->temp_color = (doom->temp_color >> 1) & 8355711;
			doom->s_pixels[d.py * doom->w + (int)x] = doom->temp_color;
			d.py++;
		}
	double floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall
	// if (doom->sight.queue[0].side == 0) column = doom->you.pos.y + doom->sight.queue[0].z * doom->sight.ray_dir.y;
    //  else           column = doom->you.pos.x + doom->sight.queue[0].z * doom->sight.ray_dir.x;
    // column -= floor((column));
	// 4 different wall directions possible
	if(doom->sight.queue[0].side == 0 && doom->sight.ray_dir.x > 0)
	{
		floorXWall = doom->sight.queue[0].x;
		floorYWall = doom->sight.queue[0].y + column;// / 64.0;// - 1;
	}
	else if(doom->sight.queue[0].side == 0 && doom->sight.ray_dir.x < 0)
	{
		floorXWall = doom->sight.queue[0].x + 1.0;
		floorYWall = doom->sight.queue[0].y + column;// / 64.0;// - 1;
	}
	else if(doom->sight.queue[0].side == 1 && doom->sight.ray_dir.y > 0)
	{
		floorXWall = doom->sight.queue[0].x + column;/// 64.0;// - 1;
		floorYWall = doom->sight.queue[0].y;
	}
	else
	{
		floorXWall = doom->sight.queue[0].x + column;// / 64.0;// - 1;
		floorYWall = doom->sight.queue[0].y + 1.0;
	}

	double distWall, distPlayer, currentDist;

	distWall = doom->sight.queue[0].z;
	distPlayer = 0.00;

	if (doom->sight.end < 0) doom->sight.end = doom->h; //becomes < 0 when the integer overflows
	int y = doom->sight.end;
	//draw the floor from drawEnd to the bottom of the screen
	while (++y < doom->h)
	{
		currentDist = doom->h / (2.0 * y - doom->h); //you could make a small lookup table for this instead

		double weight = (currentDist - distPlayer) / (distWall - distPlayer);

		double currentFloorX = weight * floorXWall + (1.0 - weight) * doom->you.pos.x;
		double currentFloorY = weight * floorYWall + (1.0 - weight) * doom->you.pos.y;
 
		SDL_Surface *tmp;
		int floorTexX, floorTexY;
		tmp = get_surface(doom, 0);
		floorTexX = (currentFloorX * tmp->w);// % tmp->w;
		floorTexX = floorTexX % tmp->w;
		floorTexY = (currentFloorY * tmp->h);// % tmp->h;
		floorTexY = floorTexY % tmp->h;

		//floor
		doom->s_pixels[(y * doom->w) + (int)x] = ((Uint32 *)tmp->pixels)[tmp->w * floorTexY + floorTexX];
		//ceiling (symmetrical!)
		doom->s_pixels[((doom->h - y) * doom->w) + (int)x] = ((Uint32 *)tmp->pixels)[tmp->w * floorTexY + floorTexX];
	}
	
}

void				draw_floor(t_doom *doom, double x, int column)
{
	//FLOOR CASTING
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
			|| (doom->map.m[(int)p->pos.y][(int)p->pos.x] == 'T')
			|| (doom->map.m[(int)p->pos.y][(int)p->pos.x] == 'C')))
		{
			p->queue[p->queue_cpt].x = p->pos.x;
			p->queue[p->queue_cpt].y = p->pos.y;
			p->queue[p->queue_cpt].side = p->side;
			p->queue[p->queue_cpt].z = calc_perp_dist(&doom->sight, &doom->you, 0);//p->queue_cpt);
			if (p->side == 1) p->queue[p->queue_cpt].tex = p->step.y < 0;
			else p->queue[p->queue_cpt].tex = (p->step.x < 0 ? 2 : 3);

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
			break;
		}
		p->cpt += 1;
	}
	return (p->cpt < p->rov ? (p->hit = 1) : 0);
}
