/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 13:20:21 by hdussert          #+#    #+#             */
/*   Updated: 2019/04/30 16:30:39 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		hooks(t_doom *doom)
{
	printf("%d, %d\n", doom->map.height, doom->map.width);
	mlx_hook(doom->window, KeyPress, KeyPressMask, key_down, doom);
	mlx_hook(doom->window, KeyRelease, KeyReleaseMask, key_up, doom);
	mlx_hook(doom->window, DestroyNotify, NoEventMask, close_window, doom);
	mlx_loop_hook(doom->mlx, loop, doom);
}

int			main(int argc, char *argv[])
{
	t_doom	doom;

	if (argc == 2)
	{
		if (ft_strcmp("/dev/zero", argv[1]) == 0)
			exit_program(NULL, ERROR_INVALID_MAP);
		init_doom(&doom);
		if (!parsing(&doom, argv[1]))
			exit_program(&doom, ERROR_INVALID_MAP);
		printf("%d, %d\n", doom.map.height, doom.map.width);
		init_mlx(&doom);
		if (!init_texture(&doom))
			exit_program(&doom, ERROR_INVALID_TEXTURES);
		init_window(&doom);
		new_player(&doom, &doom.map);
		printf("OUI\n");
		printf("%d, %d\n", doom.map.height, doom.map.width);
		hooks(&doom);
		mlx_loop(&doom.mlx);
	}
	else
		exit_program(NULL, ERROR_NOT_ENOUGH_ARGS);
	return (0);
}
