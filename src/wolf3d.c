/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 13:20:21 by hdussert          #+#    #+#             */
/*   Updated: 2019/04/05 14:15:35 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		hooks(t_wolf *w)
{
	mlx_hook(w->window, KeyPress, KeyPressMask, key_down, w);
	mlx_hook(w->window, KeyRelease, KeyReleaseMask, key_up, w);
	mlx_hook(w->window, DestroyNotify, NoEventMask, close_window, w);
	mlx_loop_hook(w->mlx, loop, w);
}

int			main(int argc, char *argv[])
{
	t_wolf	*wolf;

	if (argc == 2)
	{
		if (ft_strcmp("/dev/zero", argv[1]) == 0)
			exit_program(NULL, ERROR_INVALID_MAP);
		wolf = init_wolf();
		if (!parsing(wolf, argv[1]))
			exit_program(wolf, ERROR_INVALID_MAP);
		init_mlx(wolf);
		if (!init_texture(wolf))
			exit_program(wolf, ERROR_INVALID_TEXTURES);
		init_window(wolf);
		wolf->you = new_player(wolf, wolf->map);
		hooks(wolf);
		mlx_loop(wolf->mlx);
	}
	else
		exit_program(NULL, ERROR_NOT_ENOUGH_ARGS);
	return (0);
}
