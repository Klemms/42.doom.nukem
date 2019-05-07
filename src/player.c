/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 00:26:56 by cababou           #+#    #+#             */
/*   Updated: 2019/05/05 11:52:47 by lde-batz         ###   ########.fr       */
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
	printf("Player pos %f %f %f\n", player->pos.x, player->pos.y, player->pos.z);
}

void	teleport_player(t_player *player, double x, double y, double z)
{
	printf("Teleporting player from %f %f %f to %f %f %f\n", player->pos.x, player->pos.y, player->pos.z, x, y, z);
	fflush(stdout);
	player->pos.x = x;
	player->pos.y = y;
	player->pos.z = z;
}
