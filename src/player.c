/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 00:26:56 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 10:12:18 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	new_player(t_doom *doom, t_player *player, t_nmap *nmap)
{
	ft_bzero(player, sizeof(t_player));
	player->pos.x = get_spawn_point(nmap)->x + 0.5;
	player->pos.y = get_spawn_point(nmap)->y + 0.5;
	player->pos.z = 0.5;
	player->anglecos = -1;
	player->dir.x = -1;
	player->plane.y = 0.66;
	player->rov = 40;
	player->hud.health = 100;
	player->hud.ammo = 10;
}

void	teleport_player(t_player *player, double x, double y, double z)
{
	player->pos.x = x;
	player->pos.y = y;
	player->pos.z = z;
}
