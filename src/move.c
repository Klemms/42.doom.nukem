/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 10:12:00 by lde-batz          #+#    #+#             */
/*   Updated: 2019/05/01 14:30:45 by lde-batz         ###   ########.fr       */
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
	if (doom->keys.right == 1)
	{
		move_vec.x += player->anglecos * 0.1f;
		move_vec.y += player->anglesin * 0.1f;
	}
	if (doom->keys.right == 1)
	{
		move_vec.x -= player->anglecos * 0.1f;
		move_vec.y -= player->anglesin * 0.1f;
	}
	if (doom->keys.up == 1)
	{
		move_vec.x += player->anglesin * 0.1f;
		move_vec.y -= player->anglecos * 0.1f;
	}
	if (doom->keys.down == 1)
	{
		move_vec.x -= player->anglesin * 0.1f;
		move_vec.y += player->anglecos * 0.1f;
	}
	update_velocity2(doom, player, &move_vec);
}

void	moving(t_doom *doom)
{
	int	dest[2];

	dest[0] = doom->you.pos.x + doom->you.velocity.x;
	dest[1] = doom->you.pos.y + doom->you.velocity.y;
	if (doom->map.m[(int)doom->you.pos.y][dest[0]] != '.')
		doom->you.pos.x = dest[0] - 1e-9f;
	else
		doom->you.pos.x += doom->you.velocity.x;
	if (doom->map.m[dest[1]][(int)doom->you.pos.x] != '.')
		doom->you.pos.y = dest[1] - 1e-9f;
	else
		doom->you.pos.y += doom->you.velocity.y;
}
