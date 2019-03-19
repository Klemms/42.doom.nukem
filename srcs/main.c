/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:17:14 by lde-batz          #+#    #+#             */
/*   Updated: 2019/03/19 18:21:33 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int		main(int argc, char **argv)
{
	t_doom	doom;

//	printf("%f\n", ft_atof("-0.5"));
//	while (1);
	ft_init_doom(&doom);
	doom.game_mode = 
		argc == 2 && ft_strcmp(argv[1], "editor") == 0 ? M_EDITOR : M_GAME;
	SDL_ShowCursor(SDL_DISABLE);
	while (doom.bool_prog)
	{
		if (doom.game_mode == M_EDITOR)
		{

		}
		else if (doom.game_mode == M_GAME)
		{
			render_game(&doom);
		}
	}
	SDL_DestroyRenderer(doom.rend);
	SDL_DestroyWindow(doom.win);
	SDL_Quit();
	return (EXIT_SUCCESS);
}
