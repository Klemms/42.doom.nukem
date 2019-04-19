/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 10:20:51 by lde-batz          #+#    #+#             */
/*   Updated: 2019/04/17 17:39:05 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	ft_move_player(t_doom *doom, double dx, double dy, int new_sect)
{
	int			s;
	t_xy		p;
	t_sector	*sect;
	t_xy		*vert;
	t_xy		p_d;

	p.x = doom->player.where.x;
	p.y = doom->player.where.y;
	p_d.x = p.x + dx;
	p_d.y = p.y + dy;
	sect = &doom->sectors[doom->player.sector];
	vert = sect->vertex;
	s = -1;
	while (++s < sect->pts)
		if (sect->neighbors[s] >= 0
				&& ft_intersect_box(p, p_d, vert[s], vert[s + 1])
				&& ft_point_side(p_d, vert[s], vert[s + 1]) < 0)
		{
			doom->player.sector = new_sect;
			break ;
		}
	doom->player.where.x += dx;
	doom->player.where.y += dy;
	doom->player.anglesin = sin(doom->player.angle);
	doom->player.anglecos = cos(doom->player.angle);
}

void	ft_move_wsad2(t_move *move, t_player *player, t_xy *move_vec)
{
	int		pushing;
	double	acceleration;

	if (move->wsad[3])
	{
		move_vec->x -= player->anglesin * 0.2f;
		move_vec->y += player->anglecos * 0.2f;
	}
	pushing = move->wsad[0] || move->wsad[1] || move->wsad[2] || move->wsad[3];
	acceleration = (pushing) ? 0.4 : 0.2;
	player->velocity.x = player->velocity.x * (1 - acceleration)
		+ move_vec->x * acceleration;
	player->velocity.y = player->velocity.y * (1 - acceleration)
		+ move_vec->y * acceleration;
	if (pushing)
		move->moving = 1;
}

void	ft_move_wsad(t_doom *doom, t_move *move, t_player *player)
{
	t_xy	move_vec;

	ft_check_duck_up(doom);
	move_vec.x = 0.0;
	move_vec.y = 0.0;
	if (move->wsad[0])
	{
		move_vec.x += player->anglecos * 0.2f;
		move_vec.y += player->anglesin * 0.2f;
	}
	if (move->wsad[1])
	{
		move_vec.x -= player->anglecos * 0.2f;
		move_vec.y -= player->anglesin * 0.2f;
	}
	if (move->wsad[2])
	{
		move_vec.x += player->anglesin * 0.2f;
		move_vec.y -= player->anglecos * 0.2f;
	}
	ft_move_wsad2(move, player, &move_vec);
}

/*
int		ft_check_collision(t_moving *m)
{
	t_xy	d1;
	t_xy	d2;
	t_xy	i;
	double	d;

	if (ft_intersect_box(m->p, m->p_d, m->vert[m->s], m->vert[m->s + 1])
		&& ft_point_side(m->p_d, m->vert[m->s], m->vert[m->s + 1]) < 0)
	{
		return (1);
	}
	if (m->vert[m->s + 1].x - m->vert[m->s].x == 0)
	{
		i.x = m->vert[m->s].x;
		i.y = m->p_d.y;
	}
	else if (m->vert[m->s + 1].y - m->vert[m->s].y == 0)
	{
		i.x = m->p_d.x;
		i.y = m->vert[m->s].y;
	}
	else
	{
		d1.x = (m->vert[m->s + 1].y - m->vert[m->s].y) / (m->vert[m->s + 1].x - m->vert[m->s].x);
		d1.y = m->vert[m->s].y - (d1.x * m->vert[m->s].x);
		d2.x = -1 / d1.x;
		d2.y = m->p_d.y - d2.x * m->p_d.x;
		i.x = (d2.y - d1.y) / (d1.x - d2.x);
		i.y = d1.x * i.x + d1.y;
	}
	d = (i.x - m->p_d.x) * (i.x - m->p_d.x) + (i.y - m->p_d.y) * (i.y - m->p_d.y);
	printf("distance: %f\n", d);
	if (ft_point_side(m->p_d, m->vert[m->s], m->vert[m->s + 1]) < 0)
		d = -d;
	if (d <= 1)
		return (1);
	return (0);
}*/

void	ft_check_neighbors(t_doom *doom, t_moving *constant, t_sect_moving *m, int sect)
{
	if (constant)
		;
	m[sect].sect = &doom->sectors[sect];
	m[sect].vert = m[sect].sect->vertex;
	m[sect].s = -1;
	constant->new_sect = sect;
	while (++m[sect].s < m[sect].sect->pts)
	{
		m[sect].p_d.x = constant->p.x + constant->d.x;
		m[sect].p_d.y = constant->p.y + constant->d.y;
		if (ft_intersect_box(constant->p, m[sect].p_d, m[sect].vert[m[sect].s], m[sect].vert[m[sect].s + 1])
				&& ft_point_side(m[sect].p_d, m[sect].vert[m[sect].s], m[sect].vert[m[sect].s + 1]) < 0)
			ft_moving_check(doom, constant, m, sect);
	}
}

void	ft_moving_check(t_doom *doom, t_moving *constant, t_sect_moving *m, int sect)
{
	double	max_floor;
	double	min_ceil;
	double	c1;
	double	c2;

	max_floor = (m[sect].sect->floor > doom->sectors[m[sect].sect->neighbors[m[sect].s]].floor)
		? m[sect].sect->floor : doom->sectors[m[sect].sect->neighbors[m[sect].s]].floor;
	min_ceil = (m[sect].sect->ceil < doom->sectors[m[sect].sect->neighbors[m[sect].s]].ceil)
		? m[sect].sect->ceil : doom->sectors[m[sect].sect->neighbors[m[sect].s]].ceil;
	/* Vérifiez où se trouve le trou. */
	m[sect].hole_low = (m[sect].sect->neighbors[m[sect].s] < 0) ? 9e9 : max_floor;
	m[sect].hole_high = (m[sect].sect->neighbors[m[sect].s] < 0) ? -9e9 : min_ceil;
	/* Vérifiez si nous heurtons un mur. */
	if (m[sect].hole_high < doom->player.where.z + COLLISION_HEAD
			|| m[sect].hole_low > doom->player.where.z - doom->move.eye_h + STEP_H)
	{
		constant->tmp_i++;
		m[sect].xd = 1;
		/* Des bosses dans un mur! Glissez le long du mur. */
		m[sect].xd = m[sect].vert[m[sect].s + 1].x - m[sect].vert[m[sect].s].x;
		m[sect].yd = m[sect].vert[m[sect].s + 1].y - m[sect].vert[m[sect].s].y;
		c1 = constant->d.x * m[sect].xd + m[sect].yd * constant->d.y;
		c2 = m[sect].xd * m[sect].xd + m[sect].yd * m[sect].yd;
		constant->d.x = m[sect].xd * c1 / c2;
		constant->d.y = m[sect].yd * c1 / c2;
		doom->move.moving = 0;
	}
	else
	{
		ft_check_neighbors(doom, constant, m, m[sect].sect->neighbors[m[sect].s]);
	}
}

void	ft_moving(t_doom *doom, t_player *player)
{
	t_sect_moving	*m;
	t_moving		constant;
	int				sect;


	if (!(m = (t_sect_moving*)malloc(sizeof(t_sect_moving) * doom->num_sectors)))
		ft_quit(NULL, "Error: ft_moving: m don't malloc", 2);
	sect = player->sector;
	constant.p.x = player->where.x;
	constant.p.y = player->where.y;
	constant.d.x = player->velocity.x * doom->move.speed;
	constant.d.y = player->velocity.y * doom->move.speed;
	m[sect].sect = &doom->sectors[sect];
	m[sect].vert = m[sect].sect->vertex;

	/* Check if the player is about to cross one of the sector's edges */
	constant.tmp_i = 0;
	m[sect].i = -1;
	while (++m[sect].i < 2)
	{
		m[sect].s = -1;
		while (++m[sect].s < m[sect].sect->pts)
		{
			m[sect].p_d.x = constant.p.x + constant.d.x;
			m[sect].p_d.y = constant.p.y + constant.d.y;
			if (ft_intersect_box(constant.p, m[sect].p_d, m[sect].vert[m[sect].s], m[sect].vert[m[sect].s + 1])
					&& ft_point_side(m[sect].p_d, m[sect].vert[m[sect].s], m[sect].vert[m[sect].s + 1]) < 0)
				ft_moving_check(doom, &constant, m, sect);
		}
		if(constant.tmp_i == 0)
			m[sect].i++;
	}
	if (constant.tmp_i >= 3)
	{
		constant.d.x = 0;
		constant.d.y = 0;
	}
	ft_move_player(doom, constant.d.x, constant.d.y, constant.new_sect);
	doom->move.falling = 1;
}
