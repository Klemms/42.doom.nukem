/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:39:17 by lde-batz          #+#    #+#             */
/*   Updated: 2019/04/15 16:03:28 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

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

void	ft_move_players(t_doom *doom, double dx, double dy)
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
			doom->player.sector = sect->neighbors[s];
			break ;
		}
	doom->player.where.x += dx;
	doom->player.where.y += dy;
	doom->player.anglesin = sin(doom->player.angle);
	doom->player.anglecos = cos(doom->player.angle);
}

int		ft_check_collision(t_moving *m)
{
	t_xy	d1;
	t_xy	d2;
	t_xy	i;
	double	d;

	if (ft_intersect_box(m->p, m->p_d, m->vert[m->s], m->vert[m->s + 1])
			&& ft_point_side(m->p_d, m->vert[m->s], m->vert[m->s + 1]) < 0)
	{
//		m->change_sect = 1;
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
	if (ft_point_side(m->p_d, m->vert[m->s], m->vert[m->s + 1]) < 0)
		d = -d;
	if (d <= 1)
		return (1);
	return (0);
}

void	ft_moving_checks(t_doom *doom, t_moving *m)
{
	double	max_floor;
	double	min_ceil;
	double	c1;
	double	c2;

	max_floor = (m->sect->floor > doom->sectors[m->sect->neighbors[m->s]].floor)
		? m->sect->floor : doom->sectors[m->sect->neighbors[m->s]].floor;
	min_ceil = (m->sect->ceil < doom->sectors[m->sect->neighbors[m->s]].ceil)
		? m->sect->ceil : doom->sectors[m->sect->neighbors[m->s]].ceil;
	m->hole_low = (m->sect->neighbors[m->s] < 0) ? 9e9 : max_floor;
	m->hole_high = (m->sect->neighbors[m->s] < 0) ? -9e9 : min_ceil;
	if (m->hole_high < doom->player.where.z + COLLISION_HEAD
			|| m->hole_low > doom->player.where.z - doom->move.eye_h + STEP_H)
	{
		m->tmp_i++;
		m->xd = m->vert[m->s + 1].x - m->vert[m->s].x;
		m->yd = m->vert[m->s + 1].y - m->vert[m->s].y;
		c1 = m->d.x * m->xd + m->yd * m->d.y;
		c2 = m->xd * m->xd + m->yd * m->yd;
		m->d.x = m->xd * c1 / c2;
		m->d.y = m->yd * c1 / c2;
		doom->move.moving = 0;
	}
}

void	ft_moving(t_doom *doom, t_player *player)
{
	t_moving	m;

	m.p.x = player->where.x;
	m.p.y = player->where.y;
	m.d.x = player->velocity.x * doom->move.speed;
	m.d.y = player->velocity.y * doom->move.speed;
	m.sect = &doom->sectors[player->move_sect];
	m.vert = m.sect->vertex;
	m.tmp_i = 0;
	m.i = -1;
//	m.change_sect = 0;
	while (++m.i < 2)
	{
		m.s = -1;
		while (++m.s < m.sect->pts)
		{
			m.p_d.x = m.p.x + m.d.x;
			m.p_d.y = m.p.y + m.d.y;
			if (ft_check_collision(&m))
//			if (ft_intersect_box(m.p, m.p_d, m.vert[m.s], m.vert[m.s + 1])
//					&& ft_point_side(m.p_d, m.vert[m.s], m.vert[m.s + 1]) < 0)
			{
				printf("CHECK SLIDE\n");
				ft_moving_check(doom, &m);
			}
		}
		if(m.tmp_i == 0)
			m.i++;
	}
	if (m.tmp_i >= 3)
	{
		m.d.x = 0;
		m.d.y = 0;
	}
	ft_move_player(doom, m.d.x, m.d.y);
	doom->move.falling = 1;
}
