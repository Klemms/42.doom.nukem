/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 10:06:56 by hdussert          #+#    #+#             */
/*   Updated: 2019/02/01 13:45:34 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			pixel_put(t_wolf *w, char *ptr, int x, int y)
{
	if (x > -1 && x < w->w_width && y > -1 && y < w->w_height)
		((int *)ptr)[x + y * w->w_width] = w->temp_color;
}

int				draw(t_wolf *w)
{
	double		frametime;
	double		timefps;

	timefps = 1.0 / w->fps;
	w->oldtime = w->curtime;
	w->curtime = clock();
	frametime = (double)(w->curtime - w->oldtime) / CLOCKS_PER_SEC;
	if (frametime < timefps)
	{
		usleep((timefps - frametime) * 1000000);
		w->you->speed = timefps * 5.0;
		w->you->rotspeed = timefps * 3.0;
	}
	else
	{
		w->you->speed = frametime * 5.0;
		w->you->rotspeed = frametime * 3.0;
	}
	ft_bzero(w->image->img, w->w_width * w->w_height * 4);
	calc_lov(w);
	mlx_put_image_to_window(w->mlx, w->window, w->image->ptr, 0, 0);
	return (1);
}
