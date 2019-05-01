/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 01:32:17 by cababou           #+#    #+#             */
/*   Updated: 2019/05/01 04:30:06 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

#include "doom.h"

int				quit_event(t_doom *doom, SDL_Event sdl_event);
int				key_event(t_doom *doom, SDL_Event sdl_event);
int				zoom_event(t_doom *doom, SDL_Event sdl_event);
int				ed_mouse_button(t_doom *doom, SDL_Event sdl_event);
int				ed_mouse_motion(t_doom *doom, SDL_Event sdl_event);

#endif