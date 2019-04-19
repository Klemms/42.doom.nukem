/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 12:26:45 by lde-batz          #+#    #+#             */
/*   Updated: 2019/03/22 12:06:32 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	ft_move_mouse(t_doom *doom)
{
	int	x;
	int	y;

	x = (doom->event.motion.x - (WIN_W / 2));
	y = ((WIN_H / 2) - doom->event.motion.y);
	if ((doom->player.angle += x * 0.005f) < 0)
		doom->player.angle += PI_X_2;
	if (doom->player.angle > PI_X_2)
		doom->player.angle -= PI_X_2;
	doom->move.yaw = ft_clamp(doom->move.yaw - y * 0.005f, -5, 5);
	doom->player.yaw = doom->move.yaw - doom->player.velocity.z * 0.5f;
	SDL_WarpMouseInWindow(doom->win, WIN_W / 2, WIN_H / 2);
}
