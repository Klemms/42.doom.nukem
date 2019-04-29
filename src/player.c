/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 00:26:56 by cababou           #+#    #+#             */
/*   Updated: 2019/04/05 12:26:58 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_player	*new_player(t_wolf *w, t_map *map)
{
	t_player	*you;

	if (!(you = mmalloc(sizeof(t_player))))
		exit_program(w, ERROR_MEMORY);
	ft_bzero(you, sizeof(t_player));
	if (!(you->pos = new_vec(map->start_x + 0.5, map->start_y + 0.5, 0))
	|| !(you->dir = new_vec(-1, 0, 0))
	|| !(you->plane = new_vec(0, 0.66, 0)))
		exit_program(w, ERROR_MEMORY);
	you->speed = 0;
	you->rotspeed = 0;
	you->rov = 40;
	return (you);
}
