/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_sectors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:23:05 by lde-batz          #+#    #+#             */
/*   Updated: 2019/04/10 13:17:29 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

t_sector	*ft_new_sector(t_sector *sect, char *ground, char *ceil)
{
	t_sector	*new;

	if (!(new = (t_sector*)malloc(sizeof(t_sector))))
		exit_program(NULL, QUIT_MEMERR_BEFORE_SDLINIT);
	new->floor = ft_atof(ground);
	new->ceil = ft_atof(ceil);
	new->pts = 0;
	new->next = sect;
	return (new);
}

void		ft_vertex_of_sector(t_read *r)
{
	int	i;

	i = 2;
	while (r->split[++i][0] != 'x')
		r->sect->vertex[i - 3] = r->vertices[ft_atoi(r->split[i])];
}

void		ft_double_wall(t_sector *sect, int s)
{
	t_xy	p;
	t_xy	p1;
	t_xy	p2;
	t_xyz	d1;
	t_xyz	d2;
	t_xyz	d_deno1;
	t_xyz	d_deno2;
	t_xyz	bise;
	double	deno1;
	double	deno2;
	double	d1_d2_angle;
	double	bise_angle;
	t_xy	new_d;
	double	sp_d1_d2;
	double	d_p_new_p;
	
	if (sect->neighbors[s] < 0 && sect->neighbors[s + 1] < 0)
		p = sect->vertex[s];
	if (s == 0)
		p1 = sect->vertex[sect->pts - 1];
	else
		p1 = sect->vertex[s - 1];
	p2 = sect->vertex[s + 1];
	d1.x = p.y - p1.y;
	d1.y = p1.x - p.x;
	d1.z = -d1.x * p.x - d1.y * p.y;
	d2.x = p2.y - p.y;
	d2.y = p.x - p2.x;
	d2.z = -d2.x * p.x - d2.y * p.y;
	deno1 = sqrt(d1.x * d1.x + d1.y * d1.y);
	deno2 = sqrt(d2.x * d2.x + d2.y * d2.y);
	d_deno1.x = d1.x * deno2;
	d_deno1.y = d1.y * deno2;
	d_deno1.z = d1.z * deno2;
	d_deno2.x = d2.x * deno1;
	d_deno2.y = d2.y * deno1;
	d_deno2.z = d2.z * deno1;
	bise.x = d_deno1.x + d_deno2.x;
	bise.y = d_deno1.y + d_deno2.y;
	bise.z = d_deno1.z + d_deno2.z;
	sp_d1_d2 = -d1.y * d2.y + d1.x * -d2.x;
	d1_d2_angle = acos(sp_d1_d2 / (deno1 * deno2));
	d1_d2_angle /= 2;
	d_p_new_p = 1 / sin(d1_d2_angle);
	if (bise.x == 0)
	{
		sect->move_vert[s].x = sect->vertex[s].x;
		if (bise.y < 0)
			sect->move_vert[s].y = sect->vertex[s].y + d_p_new_p;
		else
			sect->move_vert[s].y = sect->vertex[s].y - d_p_new_p;
	}
	else if (bise.y == 0)
	{
		if (bise.x < 0)
			sect->move_vert[s].x = sect->vertex[s].x + d_p_new_p;
		else
			sect->move_vert[s].x = sect->vertex[s].x - d_p_new_p;
		sect->move_vert[s].y = sect->vertex[s].y;
	}
	else
	{
		bise_angle = atan(bise.x / bise.y);
		new_d.x = sin(bise_angle) * d_p_new_p;
		new_d.y = cos(bise_angle) * d_p_new_p;
		if (bise.x < 0 && new_d.x < 0)
			new_d.x = -new_d.x;
		if (bise.x > 0 && new_d.x > 0)
			new_d.x = -new_d.x;
		if (bise.y > 0 && new_d.y > 0)
			new_d.y = -new_d.y;
		if (bise.y < 0 && new_d.y < 0)
			new_d.y = -new_d.y;
		sect->move_vert[s].x = sect->vertex[s].x + new_d.x;
		sect->move_vert[s].y = sect->vertex[s].y + new_d.y;
	}
	printf("pts: %d | new pts: %f %f\n\n", s, sect->move_vert[s].x, sect->move_vert[s].y);
}


void		ft_move_vert(t_sector *sect)
{
	int	s;
	
	s = -1;
	while (++s < sect->pts)
	{
		if (sect->neighbors[s] < 0 && sect->neighbors[s + 1] < 0)
			ft_double_wall(sect, s);
	}
	sect->move_vert[sect->pts] = sect->move_vert[0];
}

void		ft_read_sectors(t_doom *doom, t_read *r)
{
	int	i;
	int	tab[128];

	if (r->vertices == NULL)
		ft_tab_vertices(r);
	doom->num_sectors++;
	r->split = ft_strsplit(r->line, ' ');
	r->sect = ft_new_sector(r->sect, r->split[1], r->split[2]);
	i = 2;
	while (r->split[++i])
		tab[i - 3] = ft_atoi(r->split[i]);
	r->sect->pts = (i - 3) / 2;
	if (!(r->sect->vertex = (t_xy*)malloc(sizeof(t_xy) * (r->sect->pts + 1))))
		exit_program(NULL, QUIT_MEMERR_BEFORE_SDLINIT);
	if (!(r->sect->neighbors = (signed char*)malloc(sizeof(signed char) *
			r->sect->pts)))
		exit_program(NULL, QUIT_MEMERR_BEFORE_SDLINIT);
	i = -1;
	while (++i < r->sect->pts)
		r->sect->vertex[i + 1] = r->vertices[tab[i]];
	r->sect->vertex[0] = r->sect->vertex[i];
	i = -1;
	while (++i < r->sect->pts)
		r->sect->neighbors[i] = tab[i + r->sect->pts];
//	ft_move_vert(r->sect);
	ft_free_split(r->split);
}

void		ft_tab_sectors(t_doom *doom, t_read *r)
{
	int			i;
	t_sector	*s;

	i = doom->num_sectors;
	if (!(doom->sectors = (t_sector*)malloc(sizeof(t_sector) * i)))
		exit_program(NULL, QUIT_MEMERR_BEFORE_SDLINIT);
	while (--i >= 0)
	{
		s = r->sect;
		doom->sectors[i] = *s;
		doom->sectors[i].next = NULL;
		r->sect = r->sect->next;
		free(s);
	}
}
