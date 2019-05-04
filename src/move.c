/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 10:12:00 by lde-batz          #+#    #+#             */
/*   Updated: 2019/05/04 09:38:27 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	update_velocity2(t_doom *doom, t_player *player, t_xy *move_vec)
{
	double acc;

	player->moving = doom->keys.right || doom->keys.left || doom->keys.up || doom->keys.down;
	acc = player->moving ? 0.4 : 0.2;
	player->velocity.x = player->velocity.x * (1 - acc) + move_vec->x * acc;
	player->velocity.y = player->velocity.y * (1 - acc) + move_vec->y * acc;
}

void	update_velocity(t_doom *doom, t_player *player)
{
	t_xy	move_vec;

	move_vec.x = 0.0;
	move_vec.y = 0.0;
	if (doom->keys.up == 1)
	{
		move_vec.x += player->anglecos * 0.1f;
		move_vec.y += player->anglesin * 0.1f;
	}
	if (doom->keys.down == 1)
	{
		move_vec.x -= player->anglecos * 0.1f;
		move_vec.y -= player->anglesin * 0.1f;
	}
	if (doom->keys.right == 1)
	{
		move_vec.x += player->anglesin * 0.1f;
		move_vec.y -= player->anglecos * 0.1f;
	}
	if (doom->keys.left == 1)
	{
		move_vec.x -= player->anglesin * 0.1f;
		move_vec.y += player->anglecos * 0.1f;
	}
	update_velocity2(doom, player, &move_vec);
}

void	moving(t_doom *doom)
{
	t_xy dest;
	int channel;
	int	tmp_pos_x;
	double t1;

	if (doom->you.moving)
	{
		channel = Mix_PlayChannel(-1, doom->scores.walk, 0);
		if (channel != 0)
			Mix_HaltChannel(channel);
	}

	t1 = 0.1;
	dest.x = doom->you.pos.x + doom->you.velocity.x;
	dest.y = doom->you.pos.y + doom->you.velocity.y;
	//!doom->nmap->map[(int)doom->you.pos.y][(int)(dest.x + t1)].collides
	//&& !doom->nmap->map[(int)doom->you.pos.y][(int)(dest.x - t1)].collides
	if (!doom->nmap->map[(int)(doom->you.pos.y - t1)][(int)(dest.x + t1)].collides
	&& !doom->nmap->map[(int)(doom->you.pos.y + t1)][(int)(dest.x - t1)].collides
	&& !doom->nmap->map[(int)(doom->you.pos.y + t1)][(int)(dest.x + t1)].collides
	&& !doom->nmap->map[(int)(doom->you.pos.y - t1)][(int)(dest.x - t1)].collides)
		doom->you.pos.x += doom->you.velocity.x;
	else
		doom->you.velocity.x = 0;
	//!doom->nmap->map[(int)(dest.y + t1)][(int)doom->you.pos.x].collides
	/*&& !doom->nmap->map[(int)(dest.y - t1)][(int)doom->you.pos.x].collides
	&&*/ 
	if (!doom->nmap->map[(int)(dest.y + t1)][(int)(doom->you.pos.x - t1)].collides
	&& !doom->nmap->map[(int)(dest.y - t1)][(int)(doom->you.pos.x + t1)].collides
	&& !doom->nmap->map[(int)(dest.y + t1)][(int)(doom->you.pos.x + t1)].collides
	&& !doom->nmap->map[(int)(dest.y - t1)][(int)(doom->you.pos.x - t1)].collides)
		doom->you.pos.y += doom->you.velocity.y;
	else
		doom->you.velocity.y = 0;
	if (doom->you.pos.x == dest.x && doom->you.pos.y == dest.y)
		if (doom->nmap->map[(int)(doom->you.pos.y + t1)][(int)(doom->you.pos.x + t1)].collides
		|| doom->nmap->map[(int)(doom->you.pos.y - t1)][(int)(doom->you.pos.x - t1)].collides
		|| doom->nmap->map[(int)(doom->you.pos.y - t1)][(int)(doom->you.pos.x + t1)].collides
		|| doom->nmap->map[(int)(doom->you.pos.y + t1)][(int)(doom->you.pos.x - t1)].collides)
		{
		//|| doom->nmap->map[(int)doom->you.pos.y][(int)doom->you.pos.x].collides)
			doom->you.pos.x -= doom->you.velocity.x;
			doom->you.pos.y -= doom->you.velocity.y;
		}
}

int		check_collision(t_doom *doom, int neighbors[2])
{
	if (doom->nmap->map[neighbors[1]][neighbors[0]].collides)
		return (1);
	return (0);
}

void	moving2(t_doom *doom)
{
	t_xy	dest;
	int channel;
	int	neighbors[2];
	int	tmp_neighbors;
	
	if (doom->you.moving)
	{
		channel = Mix_PlayChannel(-1, doom->scores.walk, 0);
		if (channel != 0)
			Mix_HaltChannel(channel);
	}
	dest.x = doom->you.pos.x + doom->you.velocity.x;
	dest.y = doom->you.pos.y + doom->you.velocity.y;
	if ((int)dest.x != (int)doom->you.pos.x && (int)dest.y != (int)doom->you.pos.y)
	{
		;
//		printf("1\n");
//		doom->you.velocity.x = 0;
//		doom->you.velocity.y = 0;
	}
	else if ((int)dest.x != (int)doom->you.pos.x || (int)dest.y != (int)doom->you.pos.y)
	{
//		printf("2\n");
		if ((int)dest.x != (int)doom->you.pos.x)
		{
			if (dest.y - (int)doom->you.pos.y <= COL || dest.y - (int)doom->you.pos.y >= 1 - COL)
			{
				neighbors[0] = (int)doom->you.pos.x;
				if (dest.y - (int)doom->you.pos.y <= COL)
					neighbors[1] = (int)doom->you.pos.y - 1;
				else
					neighbors[1] = (int)doom->you.pos.y + 1;
				if (check_collision(doom, neighbors))
					doom->you.velocity.y = 0;
			}
		}
		if ((int)dest.y != (int)doom->you.pos.y)
		{
			if (dest.x - (int)doom->you.pos.x <= COL || dest.x - (int)doom->you.pos.x >= 1 - COL)
			{
				if (dest.x - (int)doom->you.pos.x <= COL)
					neighbors[0] = (int)doom->you.pos.x - 1;
				else
					neighbors[0] = (int)doom->you.pos.x + 1;
				neighbors[1] = (int)doom->you.pos.y;
				if (check_collision(doom, neighbors))
					doom->you.velocity.x = 0;
			}
		}
	}
	else
	{
		neighbors[0] = dest.x;
		neighbors[1] = dest.y;
		if (check_collision(doom, neighbors))
		{
			doom->you.velocity.x = 0;
			doom->you.velocity.y = 0;
		}
	}
	doom->you.pos.x += doom->you.velocity.x;
	doom->you.pos.y += doom->you.velocity.y;	
}