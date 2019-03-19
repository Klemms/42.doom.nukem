/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 10:20:51 by lde-batz          #+#    #+#             */
/*   Updated: 2019/03/19 13:31:45 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	ft_move_player(t_doom *doom, double dx, double dy)
{
	int			s;
	t_xy		p;
	t_sector	*sect;
	t_xy		*vert;
	t_xy		p_d;

	p.x = doom->player.where.x;
	p.y = doom->player.where.y;
	sect = &doom->sectors[doom->player.sector];
	vert = sect->vertex;
	p_d.x = p.x + (dx * doom->move.speed);
	p_d.y = p.y + (dy * doom->move.speed);
	s = -1;
	while (++s < sect->pts)
		if (sect->neighbors[s] >= 0
				&& ft_intersect_box(p, p_d, vert[s], vert[s + 1])
				&& ft_point_side(p_d, vert[s], vert[s + 1]) < 0)
		{
			doom->player.sector = sect->neighbors[s];
			break ;
		}
	doom->player.where.x += (dx * doom->move.speed);
	doom->player.where.y += (dy * doom->move.speed);
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

void	ft_move_wsad(t_move *move, t_player *player)
{
	t_xy	move_vec;

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

void	ft_moving_check(t_doom *doom, t_moving *m)
{
	double	max_floor;
	double	min_ceil;

	max_floor = (m->sect->floor > doom->sectors[m->sect->neighbors[m->s]].floor)
		? m->sect->floor : doom->sectors[m->sect->neighbors[m->s]].floor;
	min_ceil = (m->sect->ceil < doom->sectors[m->sect->neighbors[m->s]].ceil)
		? m->sect->ceil : doom->sectors[m->sect->neighbors[m->s]].ceil;
	/* Check where the hole is. */
	m->hole_low = (m->sect->neighbors[m->s] < 0) ? 9e9 : max_floor;
	m->hole_high = (m->sect->neighbors[m->s] < 0) ? -9e9 : min_ceil;
	/* Check whether we're bumping into a wall. */
	if (m->hole_high < doom->player.where.z + COLLISION_HEAD
			|| m->hole_low > doom->player.where.z - doom->move.eye_h + STEP_H)
	{
		/* Bumps into a wall! Slide along the wall. */
		/* This formula is from Wikipedia article "vector projection". */
		m->xd = m->vert[m->s + 1].x - m->vert[m->s].x;
		m->yd = m->vert[m->s + 1].y - m->vert[m->s].y;
		m->d.x = m->xd * (m->d.x * m->xd + m->yd * m->d.y) /
			(m->xd * m->xd + m->yd * m->yd);
		m->d.y = m->yd * (m->d.x * m->xd + m->yd * m->d.y) /
			(m->xd * m->xd + m->yd * m->yd);
		doom->move.moving = 0;
	}
}

void	ft_moving(t_doom *doom, t_player *player)
{
	t_moving	m;

	m.p.x = player->where.x;
	m.p.y = player->where.y;
	m.d.x = player->velocity.x;
	m.d.y = player->velocity.y;
	m.sect = &doom->sectors[player->sector];
	m.vert = m.sect->vertex;
	/* Check if the player is about to cross one of the sector's edges */
	m.s = -1;
	while (++m.s < m.sect->pts)
	{
		m.p_d.x = m.p.x + m.d.x;
		m.p_d.y = m.p.y + m.d.y;
		if (ft_intersect_box(m.p, m.p_d, m.vert[m.s], m.vert[m.s + 1])
				&& ft_point_side(m.p_d, m.vert[m.s], m.vert[m.s + 1]) < 0)
			ft_moving_check(doom, &m);
	}
	ft_move_player(doom, m.d.x, m.d.y);
	doom->move.falling = 1;
}
