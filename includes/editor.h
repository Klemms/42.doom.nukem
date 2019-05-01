/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 01:32:17 by cababou           #+#    #+#             */
/*   Updated: 2019/05/01 23:32:49 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# define TOOL_NONE 0
# define TOOL_BLOCK 1

#include "doom.h"

int		quit_event(t_doom *doom, SDL_Event sdl_event);
int		key_event(t_doom *doom, SDL_Event sdl_event);
int		zoom_event(t_doom *doom, SDL_Event sdl_event);
int		ed_mouse_button(t_doom *doom, SDL_Event sdl_event);
int		ed_mouse_motion(t_doom *doom, SDL_Event sdl_event);

void	ed_block_c(t_doom *doom, t_el_button *b, SDL_MouseButtonEvent ev);
void	ed_none_c(t_doom *doom, t_el_button *b, SDL_MouseButtonEvent ev);

#endif