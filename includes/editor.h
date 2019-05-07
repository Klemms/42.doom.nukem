/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 01:32:17 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 22:38:07 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# include "doom.h"

enum	e_tools
{
	tool_none = 0,
	tool_block = 1,
	tool_textures = 2,
	tool_sprite = 3
};

int		quit_event(t_doom *doom, SDL_Event sdl_event);
int		key_event(t_doom *doom, SDL_Event sdl_event);
int		zoom_event(t_doom *doom, SDL_Event sdl_event);
int		ed_mouse_button(t_doom *doom, SDL_Event sdl_event);
int		ed_mouse_motion(t_doom *doom, SDL_Event sdl_event);
void	edit_button_render(t_doom *d, t_editor *e);

void	ed_block_c(t_doom *doom, t_el_button *b, SDL_MouseButtonEvent ev);
void	ed_none_c(t_doom *doom, t_el_button *b, SDL_MouseButtonEvent ev);
void	ed_sprite_c(t_doom *doom, t_el_button *b, SDL_MouseButtonEvent ev);

#endif
