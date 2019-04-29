/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_manip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 00:06:45 by cababou           #+#    #+#             */
/*   Updated: 2019/02/22 15:07:02 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf3d.h"

t_image		*new_screen_image(t_wolf *w)
{
	t_image		*img;

	if (!(img = (t_image *)malloc(sizeof(t_image)))
		|| !(img->ptr = mlx_new_image(w->mlx, w->w_width, w->w_height)))
		exit_program(w, ERROR_MEMORY);
	img->img = mlx_get_data_addr(img->ptr, &img->bpp, &img->s_l, &img->endian);
	return (img);
}
