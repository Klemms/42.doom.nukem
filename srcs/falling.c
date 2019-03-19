/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   falling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 12:35:09 by lde-batz          #+#    #+#             */
/*   Updated: 2019/03/19 15:11:29 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	ft_falling(t_doom *doom)
{
	double	next_z;

	doom->player.velocity.z -= 0.05f; /* Add gravity */
	next_z = doom->player.where.z + doom->player.velocity.z;
	// When going down
	if (doom->player.velocity.z < 0 && next_z
			< doom->sectors[doom->player.sector].floor + doom->move.eye_h)
	{
		/* Fix to ground */
		doom->player.where.z = doom->sectors[doom->player.sector].floor
			+ doom->move.eye_h;
		doom->player.velocity.z = 0;
		doom->move.falling = 0;
		doom->move.ground = 1;
	}
	else if (doom->player.velocity.z > 0
			&& next_z > doom->sectors[doom->player.sector].ceil) // When going up
	{
		/* Prevent jumping above ceiling */
		doom->player.velocity.z = 0;
		doom->move.falling = 1;
	}
	if (doom->move.falling)
	{
		doom->player.where.z += doom->player.velocity.z;
		doom->move.moving = 1;
	}
}
