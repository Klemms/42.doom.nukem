/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 19:46:06 by lde-batz          #+#    #+#             */
/*   Updated: 2019/05/07 11:43:01 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	press_button(t_doom *doom)
{
	int	pos_x;
	int	pos_y;
	int	orientation;

	pos_x = (int)doom->you.pos.x;
	pos_y = (int)doom->you.pos.y;
	if (doom->you.angle < N_3_PI_4 && doom->you.angle >= P_3_PI_4)
	{
		pos_x -= 1;
		orientation = 0;
	}
	else if (doom->you.angle < N_PI_4)
	{
		pos_y -= 1;
		orientation = 1;
	}
	else if (doom->you.angle < M_PI_4)
	{
		pos_x += 1;
		orientation = 0;
	}
	else
	{
		pos_y += 1;
		orientation = 1;
	}
	if (doom->nmap->map[pos_y][pos_x].block_type == block_button
	&& doom->nmap->map[pos_y][pos_x].orientation == orientation)
		;
}
