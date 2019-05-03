/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 00:26:56 by cababou           #+#    #+#             */
/*   Updated: 2019/05/02 12:34:44 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	new_player(t_doom *doom, t_player *player, t_map *map)
{
	ft_bzero(player, sizeof(t_player));
	player->pos.x = map->start_x + 0.5;
	player->pos.y = map->start_y + 0.5;
	player->anglecos = -1;
	player->dir.x = -1;
	player->plane.y = 0.66;
	player->rov = 40;
}
