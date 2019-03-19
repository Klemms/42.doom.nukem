/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:17:14 by lde-batz          #+#    #+#             */
/*   Updated: 2019/03/19 17:49:12 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	ft_limit_fps(unsigned int limit)
{
	unsigned int	ticks;

	ticks = SDL_GetTicks();
	if (ticks > limit)
		return ;
	else if (ticks + 16 < limit)
		SDL_Delay(FPS_LIMIT);
	else
		SDL_Delay(limit - ticks);
}

int		main(void)
{
	t_doom	doom;
	int		frame_limit;

	ft_init_doom(&doom);
	SDL_ShowCursor(SDL_DISABLE);
	while (doom.bool_prog)
	{
		SDL_RenderClear(doom.rend);
		doom.surface = SDL_GetWindowSurface(doom.win);
		ft_print_screen(&doom);
		SDL_UpdateWindowSurface(doom.win);
		frame_limit = SDL_GetTicks() + FPS_LIMIT;
		ft_limit_fps(frame_limit);
		frame_limit = SDL_GetTicks() + FPS_LIMIT;
        /* Vertical collision detection */
		doom.move.eye_h = (doom.move.ducking) ? DUCK_CAM_H : CAM_H;
		doom.move.ground = !doom.move.falling;
		if (doom.move.falling)
			ft_falling(&doom);
        /* Horizontal collision detection */
		if (doom.move.moving)
			ft_moving(&doom, &doom.player);
		while (SDL_PollEvent(&doom.event))
			ft_event(&doom);
		ft_move_player(&doom, 0, 0);
		ft_move_wsad(&doom, &doom.move, &doom.player);
	}
	SDL_DestroyRenderer(doom.rend);
	SDL_DestroyWindow(doom.win);
	SDL_Quit();
	return (EXIT_SUCCESS);
}
