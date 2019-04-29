/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 23:44:05 by cababou           #+#    #+#             */
/*   Updated: 2019/04/05 14:16:32 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf3d.h"

void	normecchiant(t_wolf *w)
{
	w->oldtime = 0;
	w->curtime = 0;
	w->fps = 60.0;
	w->you = NULL;
	w->texture[0].img.ptr = NULL;
	w->texture[1].img.ptr = NULL;
	w->texture[2].img.ptr = NULL;
	w->texture[3].img.ptr = NULL;
	w->mlx = NULL;
	w->image = NULL;
}

t_wolf	*init_wolf(void)
{
	t_wolf *w;

	if (!(w = mmalloc(sizeof(t_wolf))))
		exit_program(NULL, ERROR_MEMORY);
	ft_bzero(w, sizeof(t_wolf));
	if (!(w->keys = mmalloc(sizeof(t_key)))
		|| !(w->map = mmalloc(sizeof(t_map)))
		|| !(w->textures = lstcontainer_new())
		|| !(w->sight = mmalloc(sizeof(t_sight))))
		exit_program(NULL, ERROR_MEMORY);
	w->w_width = 1200;
	w->w_height = 800;
	w->map->height = 0;
	w->map->width = 0;
	w->map->start_x = 0;
	w->map->start_y = 0;
	w->map->m = NULL;
	w->keys->left = 0;
	w->keys->right = 0;
	w->keys->up = 0;
	w->keys->down = 0;
	w->keys->shadow = 0;
	normecchiant(w);
	return (w);
}

void	init_mlx(t_wolf *w)
{
	if (!(w->mlx = mlx_init()))
		exit_program(w, ERROR_MLX_INIT);
	w->image = new_screen_image(w);
}

void	init_window(t_wolf *w)
{
	if (!(w->window = mlx_new_window(w->mlx, w->w_width, w->w_height,
		"Wolf 3D")))
		exit_program(w, ERROR_MLX_WINDOW_INIT);
}
