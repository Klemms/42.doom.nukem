/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 19:46:06 by lde-batz          #+#    #+#             */
/*   Updated: 2019/05/07 23:45:39 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	check_event_id(t_doom *doom, int pos_x, int pos_y)
{
	int	i;
	int j;
	int id;

	doom->you.hud.key -= 1;
	doom->nmap->map[pos_y][pos_x].state = 1;
	id = doom->nmap->map[pos_y][pos_x].event_id;
	i = -1;
	while (++i < doom->nmap->size_y)
	{
		j = -1;
		while (++j < doom->nmap->size_x)
		{
			if (doom->nmap->map[i][j].event_id == id
			&& doom->nmap->map[i][j].block_type == block_door)
			{
				doom->nmap->map[i][j].collides = 0;
				doom->nmap->map[i][j].state = 1;
			}
		}
	}
}

void	press_button2(t_doom *doom, int *pos_x, int *pos_y, int *orientation)
{
	if (doom->you.angle < M_PI_4)
	{
		*pos_x += 1;
		*orientation = 0;
	}
	else
	{
		*pos_y += 1;
		*orientation = 1;
	}
}

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
	else
		press_button2(doom, &pos_x, &pos_y, &orientation);
	if (doom->nmap->map[pos_y][pos_x].block_type == block_button
	&& doom->nmap->map[pos_y][pos_x].orientation == orientation
	&& !doom->nmap->map[pos_y][pos_x].state && doom->you.hud.key > 0)
		check_event_id(doom, pos_x, pos_y);
}
