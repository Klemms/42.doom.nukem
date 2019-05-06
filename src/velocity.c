/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   velocity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:06:32 by lde-batz          #+#    #+#             */
/*   Updated: 2019/05/06 15:06:53 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	update_velocity2(t_doom *doom, t_player *player, t_xy *move_vec
																, float speed)
{
	float acc;

	if (doom->keys.right == 1)
	{
		move_vec->x += player->anglesin * speed;
		move_vec->y -= player->anglecos * speed;
	}
	if (doom->keys.left == 1)
	{
		move_vec->x -= player->anglesin * speed;
		move_vec->y += player->anglecos * speed;
	}
	player->moving = doom->keys.right || doom->keys.left
		|| doom->keys.up || doom->keys.down;
	acc = player->moving ? 0.4 : 0.3;
	player->velocity.x = player->velocity.x * (1 - acc) + move_vec->x * acc;
	player->velocity.y = player->velocity.y * (1 - acc) + move_vec->y * acc;
}

void	update_velocity(t_doom *doom, t_player *player)
{
	t_xy	move_vec;
	float	speed;

	speed = 0.1;
	if ((doom->keys.up == 1 || doom->keys.down == 1) && (doom->keys.left == 1
	|| doom->keys.right == 1))
		speed = 0.07071;
	if (doom->you.is_sprinting)
		speed *= 2;
	if (doom->you.is_crouching)
		speed /= 2;
	move_vec.x = 0.0;
	move_vec.y = 0.0;
	if (doom->keys.up == 1)
	{
		move_vec.x += player->anglecos * speed;
		move_vec.y += player->anglesin * speed;
	}
	if (doom->keys.down == 1)
	{
		move_vec.x -= player->anglecos * speed;
		move_vec.y -= player->anglesin * speed;
	}
	update_velocity2(doom, player, &move_vec, speed);
}
