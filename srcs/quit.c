/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:54:21 by lde-batz          #+#    #+#             */
/*   Updated: 2019/04/18 05:13:38 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	quit_it(t_doom *doom, int code, char *message)
{
	// TODO: Free doom for REAL
	if (doom)
		free(doom);
	ft_putendl(message);
	destroy_fonts(doom);
	SDL_Quit();
	exit(code);
}

void	exit_program(t_doom *d, int err_code)
{
	SDL_ShowCursor(SDL_ENABLE);
	if (d)
		SDL_SetWindowGrab(d->win, SDL_FALSE);
	if (err_code >= 0)
		SDL_DestroyRenderer(d->rend);
	if (err_code >= 0)
		SDL_DestroyWindow(d->win);
	if (err_code == QUIT_CANT_FIND_MAP)
		quit_it(d, err_code, "Cannot find map.");
	if (err_code == QUIT_CANT_INIT_SDL)
		quit_it(d, err_code, "SDL initialization failed.");
	if (err_code == QUIT_CANT_INIT_WINDOW)
		quit_it(d, err_code, "Window initialization failed.");
	if (err_code == QUIT_CANT_INIT_RENDERER)
		quit_it(d, err_code, "Renderer initialization failed.");
	if (err_code == QUIT_MEMERR_BEFORE_SDLINIT
		|| err_code == QUIT_MEMERR_AFTER_SDLINIT)
		quit_it(d, err_code, "Memory error.");
	quit_it(d, 0, "Exiting Doom Nukem");
}