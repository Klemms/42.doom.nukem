/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wfc_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 23:33:40 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 23:45:25 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	wfc_wall_draw(t_raycasting *rc, Uint32 **canvas)
{
	int			d;
	Uint32		color;
	int			y;

	y = rc->draw_start - 1;
	while (++y < rc->draw_end)
	{
		d = ((int)(y - (WIN_H * rc->p_z)) << 8) + ((int)rc->lineHeight << 7);
		rc->tex.y = ((d * rc->texture->h) / rc->lineHeight) >> 8;
		rc->tex.y = rc->tex.y % rc->texture->h;
		color = ((Uint32 *)rc->texture->pixels)[rc->texture->w
			* rc->tex.y + rc->tex.x];
		if (rc->side == 1)
			color = (color >> 1) & 8355711;
		(*canvas)[y * WIN_W + rc->x] = color;
	}
}

void	wfc_floor_draw(t_raycasting *rc, t_player *p, Uint32 **canvas)
{
	t_norme2	n;

	n.distWall = rc->perp_wall_dist;
	n.distPlayer = 0.0;
	n.y = rc->draw_end;
	while (++n.y < WIN_H)
	{
		n.currentDist = WIN_H / (2.0 * (n.y - (WIN_H * rc->p_z)));
		n.weight = (n.currentDist - n.distPlayer) / (n.distWall - n.distPlayer);
		n.currentFloorX = n.weight * rc->floor.x + (1.0 - n.weight) * p->pos.x;
		n.currentFloorY = n.weight * rc->floor.y + (1.0 - n.weight) * p->pos.y;
		rc->floor_tex.x = (int)(n.currentFloorX * rc->texture->w)
			% rc->texture->w;
		rc->floor_tex.y = (int)(n.currentFloorY * rc->texture->h)
			% rc->texture->h;
		(*canvas)[n.y * WIN_W + rc->x] = (((Uint32 *)rc->texture->pixels)
			[rc->texture->w * rc->floor_tex.y + rc->floor_tex.x] >> 1)
				& 8355711;
	}
}

void	wfc_ceiling_draw(t_raycasting *rc, t_player *p, Uint32 **canvas)
{
	t_norme2	n;

	n.distWall = rc->perp_wall_dist;
	n.distPlayer = 0.0;
	n.y = 0;
	while (++n.y < rc->draw_start)
	{
		n.currentDist = WIN_H / (((WIN_H * rc->p_z) - n.y) * 2.0);
		n.weight = (n.currentDist - n.distPlayer) / (n.distWall - n.distPlayer);
		n.currentFloorX = n.weight * rc->floor.x + (1.0 - n.weight) * p->pos.x;
		n.currentFloorY = n.weight * rc->floor.y + (1.0 - n.weight) * p->pos.y;
		rc->floor_tex.x = (int)(n.currentFloorX * rc->texture->w)
			% rc->texture->w;
		rc->floor_tex.y = (int)(n.currentFloorY * rc->texture->h)
			% rc->texture->h;
		(*canvas)[n.y * WIN_W + rc->x] = ((Uint32 *)rc->texture->pixels)
			[rc->texture->w * rc->floor_tex.y + rc->floor_tex.x];
	}
}

void	draw_wfc2(t_doom *doom, double **z_buffer)
{
	wfc_wall_init(&doom->raycasting, &doom->you);
	wfc_wall_draw(&doom->raycasting, &doom->s_pixels);
	(*z_buffer)[doom->raycasting.x] = doom->raycasting.perp_wall_dist;
	wfc_fc_init(&doom->raycasting);
	doom->raycasting.texture = get_surface(doom, 0);
	wfc_floor_draw(&doom->raycasting, &doom->you, &doom->s_pixels);
	doom->raycasting.texture = get_surface(doom, 1);
	wfc_ceiling_draw(&doom->raycasting, &doom->you, &doom->s_pixels);
}

void	draw_wfc(t_doom *doom, double **z_buffer)
{
	wfc_init(&doom->raycasting, &doom->you);
	wfc_rayhit(&doom->raycasting, &doom->you, doom->nmap);
	if (doom->raycasting.side == 0)
	{
		if (doom->raycasting.step.x < 0)
			doom->raycasting.texture = get_surface(doom, doom->nmap->map
				[doom->raycasting.map.y][doom->raycasting.map.x].n_texture);
		else
			doom->raycasting.texture = get_surface(doom, doom->nmap->map
				[doom->raycasting.map.y][doom->raycasting.map.x].s_texture);
	}
	else
	{
		if (doom->raycasting.step.y < 0)
			doom->raycasting.texture = get_surface(doom, doom->nmap->map
				[doom->raycasting.map.y][doom->raycasting.map.x].w_texture);
		else
			doom->raycasting.texture = get_surface(doom, doom->nmap->map
				[doom->raycasting.map.y][doom->raycasting.map.x].e_texture);
	}
	draw_wfc2(doom, z_buffer);
}
