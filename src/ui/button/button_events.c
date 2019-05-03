/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 04:32:39 by cababou           #+#    #+#             */
/*   Updated: 2019/05/03 05:17:58 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		button_click(t_doom *doom, SDL_Event sdl_event)
{
	t_list					*tmp;
	t_el_button				*tmp_button;
	SDL_MouseButtonEvent	event;

	if (sdl_event.type != SDL_MOUSEBUTTONUP)
		return (0);
	event = sdl_event.button;
	tmp = doom->buttons->firstelement;
	while (tmp)
	{
		tmp_button = (t_el_button *)tmp->content;
		if (tmp_button->is_visible && !tmp_button->is_disabled)
			if (button_coords_contained(tmp_button, event.x, event.y))
			{
				tmp_button->ui_callback(doom, tmp_button, event);
				return (1);
			}
		tmp = tmp->next;
	}
	return (1);
}
