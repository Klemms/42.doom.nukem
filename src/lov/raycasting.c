/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 11:20:18 by hdussert          #+#    #+#             */
/*   Updated: 2019/05/07 23:10:30 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	draw_screen(t_doom *doom)
{
	double	**z_buffer;

	doom->raycasting.x = -1;
	z_buffer = malloc(sizeof(double *));
	*z_buffer = malloc(sizeof(double) * WIN_W);
	while (++doom->raycasting.x < WIN_W)
		draw_wfc(doom, z_buffer);
	doom->lsprite.spritesOrder = malloc(sizeof(int)
		* doom->lsprite.numbSprites);
	doom->lsprite.spritesDist = malloc(sizeof(double)
		* doom->lsprite.numbSprites);
	draw_sprites(doom, &doom->raycasting, &doom->you, z_buffer,
		&doom->s_pixels, &doom->lsprite);
	free(*z_buffer);
	free(z_buffer);
	free(doom->lsprite.spritesOrder);
	free(doom->lsprite.spritesDist);
}
