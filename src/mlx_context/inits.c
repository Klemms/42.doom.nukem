/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 23:44:05 by cababou           #+#    #+#             */
/*   Updated: 2019/04/30 14:25:05 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../doom.h"

void	normecchiant(t_doom *doom)
{
	doom->oldtime = 0;
	doom->curtime = 0;
	doom->fps = 60.0;
	doom->texture[0].ptr = NULL;
	doom->texture[1].ptr = NULL;
	doom->texture[2].ptr = NULL;
	doom->texture[3].ptr = NULL;
	doom->mlx = NULL;
}

void	init_doom(t_doom *doom)
{
	if (!(doom->textures = lstcontainer_new()))
		exit_program(NULL, ERROR_MEMORY);
	doom->w_width = 1200;
	doom->w_height = 800;
	doom->map.height = 0;
	doom->map.width = 0;
	doom->map.start_x = 0;
	doom->map.start_y = 0;
	doom->map.m = NULL;
	doom->keys.left = 0;
	doom->keys.right = 0;
	doom->keys.w = 0;
	doom->keys.s = 0;
	doom->keys.a = 0;
	doom->keys.d = 0;
	doom->keys.shadow = 0;
	normecchiant(doom);
}

void	init_mlx(t_doom *doom)
{
	if (!(doom->mlx = mlx_init()))
		exit_program(doom, ERROR_MLX_INIT);
	new_screen_image(doom, &doom->img, doom->w_width, doom->w_height);
}

void	init_window(t_doom *doom)
{
	if (!(doom->window = mlx_new_window(doom->mlx, doom->w_width, doom->w_height,
		"Doom Nukem")))
		exit_program(doom, ERROR_MLX_WINDOW_INIT);
}
