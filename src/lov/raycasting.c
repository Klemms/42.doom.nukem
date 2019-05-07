/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 11:20:18 by hdussert          #+#    #+#             */
/*   Updated: 2019/05/04 09:43:07 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void    draw_screen(t_doom *doom)
{
  doom->raycasting.x = -1;
  doom->raycasting.texture = get_surface(doom, 2);

  double    **z_buffer;
  z_buffer = malloc(sizeof(double *));
  *z_buffer = malloc(sizeof(double) * WIN_W);
  while (++doom->raycasting.x < WIN_W)
  draw_wfc(doom, z_buffer);
  draw_sprites(doom, &doom->raycasting, &doom->you, z_buffer, &doom->s_pixels, &doom->lsprite);
  free(*z_buffer);
  free(z_buffer);
}