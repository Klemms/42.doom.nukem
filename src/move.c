/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 10:12:00 by lde-batz          #+#    #+#             */
/*   Updated: 2019/05/02 18:12:21 by lde-batz         ###   ########.fr       */
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
	int	dest[2];
	int channel;
	int	tmp_pos_x;
	t_xy	collision;

	channel = Mix_PlayChannel(-1, doom->scores.walk, 0);
	if (channel != 0)
		Mix_HaltChannel(channel);
	collision.x = (doom->you.velocity.x < 0) ? doom->you.velocity.x - 0.2 : doom->you.velocity.x + 0.2;
	collision.y = (doom->you.velocity.y < 0) ? doom->you.velocity.y - 0.2 : doom->you.velocity.y + 0.2;
	tmp_pos_x = doom->you.pos.x;
	dest[0] = doom->you.pos.x + collision.x;
	dest[1] = doom->you.pos.y + collision.y;
	if (doom->map.m[(int)doom->you.pos.y][dest[0]] != '.')
	{
		if (doom->you.velocity.x < 0)
			doom->you.pos.x = dest[0] + 1 + 0.2;
		else
			doom->you.pos.x = dest[0] - 0.2;
	}
	else
		doom->you.pos.x += doom->you.velocity.x;
	if (doom->map.m[dest[1]][tmp_pos_x] != '.')
	{
		if (doom->you.velocity.y < 0)
			doom->you.pos.y = dest[1] + 1 + 0.2;
		else
			doom->you.pos.y = dest[1] - 0.2;
	}
	else
		doom->you.pos.y += doom->you.velocity.y;
	doom->you.moving = 0;
}
