/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:29:49 by cababou           #+#    #+#             */
/*   Updated: 2019/04/17 02:30:20 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

void	editor_init_events(t_doom *doom)
{
	if ((doom->events = lstcontainer_new()) == NULL)
		exit_program(doom, QUIT_MEMERR_AFTER_SDLINIT);
}

void	editor_distribute_events(t_doom *doom, SDL_Event sdl_event)
{
	t_list				*list;
	t_registered_event	*event;

	list = doom->events->firstelement;
	while (list)
	{
		event = (t_registered_event *)list->content;
		if (event->type == sdl_event.type)
		{
			event->handler(doom, sdl_event);
		}
		list = list->next;
	}
}

void	editor_register_event(t_doom *doom, Uint32 type,
			int (*handler)(t_doom *d, SDL_Event ev))
{
	t_registered_event	*event;

	if ((event = malloc(sizeof(t_registered_event))) == NULL)
		exit_program(doom, QUIT_MEMERR_AFTER_SDLINIT);
	event->type = type;
	event->handler = handler;
	lstcontainer_add(doom->events, event);
}