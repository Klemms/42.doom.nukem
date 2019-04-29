/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 01:32:17 by cababou           #+#    #+#             */
/*   Updated: 2019/04/19 04:24:41 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

#include "doom.h"

int				quit_event(t_doom *doom, SDL_Event sdl_event);
int				key_event(t_doom *doom, SDL_Event sdl_event);

#endif