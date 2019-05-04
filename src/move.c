/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 10:12:00 by lde-batz          #+#    #+#             */
/*   Updated: 2019/05/04 09:11:35 by cababou          ###   ########.fr       */
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

void	moving2(t_doom *doom)
{
	int	dest[2];
	int channel;
	int	tmp_pos_x;
	t_xy	collision;

	if (doom->you.moving)
	{
		channel = Mix_PlayChannel(-1, doom->scores.walk, 0);
		if (channel != 0)
			Mix_HaltChannel(channel);
	}
	collision.x = (doom->you.velocity.x < 0) ? doom->you.velocity.x - COL : doom->you.velocity.x + COL;
	collision.y = (doom->you.velocity.y < 0) ? doom->you.velocity.y - COL : doom->you.velocity.y + COL;
	tmp_pos_x = doom->you.pos.x;
	dest[0] = doom->you.pos.x + collision.x;
	dest[1] = doom->you.pos.y + collision.y;
	if (doom->nmap->map[(int)doom->you.pos.y][dest[0]].collides)
	{
		if (doom->you.velocity.x < 0)
			doom->you.pos.x = dest[0] + 1 + COL;
		else
			doom->you.pos.x = dest[0] - COL;
	}
	else
		doom->you.pos.x += doom->you.velocity.x;
	if (doom->nmap->map[dest[1]][tmp_pos_x].collides)
	{
		if (doom->you.velocity.y < 0)
			doom->you.pos.y = dest[1] + 1 + COL;
		else
			doom->you.pos.y = dest[1] - COL;
	}
	else
		doom->you.pos.y += doom->you.velocity.y;
	doom->you.moving = 0;
}

int		check_collision(t_doom *doom, int neighbors[2])
{
	if (doom->map.m[neighbors[1]][neighbors[0]] != '.')
		return (1);
	return (0);
}

void	moving(t_doom *doom)
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
	else if ((dest.x - (int)doom->you.pos.x <= COL || dest.x - (int)doom->you.pos.x >= 1 - COL)
	&& (dest.y - (int)doom->you.pos.y <= COL || dest.y - (int)doom->you.pos.y >= 1 - COL))
	{
//		printf("3\n");
		if (dest.x - (int)doom->you.pos.x <= COL)
			neighbors[0] = (int)doom->you.pos.x - 1;
		else
			neighbors[0] = (int)doom->you.pos.x + 1;
		neighbors[1] = (int)doom->you.pos.y;
		if (check_collision(doom, neighbors))
			doom->you.velocity.x = 0;
		tmp_neighbors = neighbors[0];
		neighbors[0] = (int)doom->you.pos.x;
		if (dest.y - (int)doom->you.pos.y <= COL)
			neighbors[1] = (int)doom->you.pos.y - 1;
		else
			neighbors[1] = (int)doom->you.pos.y + 1;
		if (check_collision(doom, neighbors))
			doom->you.velocity.y = 0;
		neighbors[0] = tmp_neighbors;
		if (check_collision(doom, neighbors) && doom->you.velocity.x != 0 && doom->you.velocity.y != 0)
		{
			if (fabs(round(dest.x) - dest.x) > fabs(round(dest.y) - dest.y))
				doom->you.velocity.x = 0;
			else
				doom->you.velocity.y = 0;
		}
	}
	else if (dest.x - (int)doom->you.pos.x <= COL || dest.x - (int)doom->you.pos.x >= 1 - COL)
	{
//		printf("4\n");
		if (dest.x - (int)doom->you.pos.x <= COL)
			neighbors[0] = (int)doom->you.pos.x - 1;
		else
			neighbors[0] = (int)doom->you.pos.x + 1;
		neighbors[1] = (int)doom->you.pos.y;
		if (check_collision(doom, neighbors))
			doom->you.velocity.x = 0;
	}
	else if (dest.y - (int)doom->you.pos.y <= COL || dest.y - (int)doom->you.pos.y >= 1 - COL)
	{
//		printf("5\n");
		neighbors[0] = (int)doom->you.pos.x;
		if (dest.y - (int)doom->you.pos.y <= COL)
			neighbors[1] = (int)doom->you.pos.y - 1;
		else
			neighbors[1] = (int)doom->you.pos.y + 1;
		if (check_collision(doom, neighbors))
			doom->you.velocity.y = 0;
	}
	doom->you.pos.x += doom->you.velocity.x;
	doom->you.pos.y += doom->you.velocity.y;	
}