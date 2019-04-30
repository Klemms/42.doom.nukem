/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 00:26:56 by cababou           #+#    #+#             */
/*   Updated: 2019/04/30 16:19:48 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	new_player(t_doom *doom, t_map *map)
{
	doom->you.pos.x = map->start_x + 0.5;
	doom->you.pos.y = map->start_y + 0.5;
	doom->you.pos.z = 0;
	doom->you.velocity.x = 0;
	doom->you.velocity.y = 0;
	doom->you.velocity.z = 0;
	doom->you.angle = 0;
	doom->you.anglecos = 1;
	doom->you.angle = 0;
	doom->you.pitch = 0;
	doom->you.dir.x = -1;
	doom->you.dir.y = 0;
	doom->you.dir.z = 0;
	doom->you.plane.x = 0;
	doom->you.plane.y = 0.66;
	doom->you.plane.z = 0;
	doom->you.speed = 0;
	doom->you.rotspeed = 0;
	doom->you.rov = 40;
}
