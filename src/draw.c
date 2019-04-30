/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 10:06:56 by hdussert          #+#    #+#             */
/*   Updated: 2019/04/30 14:26:43 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			pixel_put(t_doom *doom, char *ptr, int x, int y)
{
	if (x > -1 && x < doom->w_width && y > -1 && y < doom->w_height)
		((int *)ptr)[x + y * doom->w_width] = doom->temp_color;
}

void			draw(t_doom *doom)
{
	double		frametime;
	double		timefps;

	timefps = 1.0 / doom->fps;
	doom->oldtime = doom->curtime;
	doom->curtime = clock();
	frametime = (double)(doom->curtime - doom->oldtime) / CLOCKS_PER_SEC;
	if (frametime < timefps)
	{
		usleep((timefps - frametime) * 1000000);
		doom->you.speed = timefps * 5.0;
		doom->you.rotspeed = timefps * 3.0;
	}
	else
	{
		doom->you.speed = frametime * 5.0;
		doom->you.rotspeed = frametime * 3.0;
	}
	ft_bzero(doom->img.img, doom->w_width * doom->w_height * 4);
	calc_lov(doom);
	mlx_put_image_to_window(doom->mlx, doom->window, doom->img.ptr, 0, 0);
}
