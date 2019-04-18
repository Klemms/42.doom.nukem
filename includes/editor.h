/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 01:32:17 by cababou           #+#    #+#             */
/*   Updated: 2019/04/17 02:25:28 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

#include "doom.h"

typedef struct			s_registered_event
{
	Uint32				type;
	int					(*handler)(t_doom *doom, SDL_Event ev);
}						t_registered_event;

void			editor_init_events(t_doom *doom);
int				editor_event_handler(t_doom *doom, SDL_Event sdl_event);
void			editor_register_event(t_doom *doom, Uint32 type,
					int (handler)(t_doom *doom, SDL_Event ev));
void			editor_distribute_events(t_doom *doom, SDL_Event sdl_event);

#endif