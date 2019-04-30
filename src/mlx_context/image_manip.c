/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_manip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 00:06:45 by cababou           #+#    #+#             */
/*   Updated: 2019/04/30 14:24:46 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../doom.h"

void	new_screen_image(t_doom *doom, t_image *img, int w, int h)
{
	if (!(img->ptr = mlx_new_image(doom->mlx, w, h)))
		exit_program(doom, ERROR_MEMORY);
	img->img = mlx_get_data_addr(img->ptr, &img->bpp, &img->s_l, &img->endian);
}
