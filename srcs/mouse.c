/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 12:26:45 by lde-batz          #+#    #+#             */
/*   Updated: 2019/04/18 03:04:57 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	ft_move_mouse(t_doom *doom)
{
	int	x;
	int	y;

	x = (doom->event.motion.x - (doom->settings->window_width / 2));
	y = ((doom->settings->window_height / 2) - doom->event.motion.y);
	doom->player.angle += x * 0.005f;
	doom->move.yaw = ft_clamp(doom->move.yaw - y * 0.005f, -5, 5);
	doom->player.yaw = doom->move.yaw - doom->player.velocity.z * 0.5f;
	SDL_WarpMouseInWindow(doom->win, doom->settings->window_width / 2,
		doom->settings->window_height / 2);
}
