/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 04:16:03 by cababou           #+#    #+#             */
/*   Updated: 2019/04/29 21:44:17 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "editor.h"

int		quit_event(t_doom *doom, SDL_Event sdl_event)
{
	exit_program(doom, ERROR_GENERIC);

	return (0);
}

int		key_event(t_doom *doom, SDL_Event sdl_event)
{
	if (sdl_event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		exit_program(doom, ERROR_GENERIC);

	return (0);
}