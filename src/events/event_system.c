/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_system.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:29:49 by cababou           #+#    #+#             */
/*   Updated: 2019/05/06 15:41:19 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_events(t_doom *doom)
{
	if ((doom->events = lstcontainer_new()) == NULL)
		exit_program(doom, ERROR_SDL_AFTER_INIT);
}

void	distribute_events(t_doom *doom, SDL_Event sdl_event)
{
	t_list				*list;
	t_registered_event	*event;

	list = doom->events->firstelement;
	while (list)
	{
		event = (t_registered_event *)list->content;
		if (event->type == sdl_event.type
			&& doom->game_mode == event->gamemode)
		{
			event->handler(doom, sdl_event);
		}
		list = list->next;
	}
	ft_lstdel(list, 1);
}

void	register_event(t_doom *doom, Uint32 type,
			int (*handler)(t_doom *d, SDL_Event ev))
{
	t_registered_event	*event;

	if ((event = mmalloc(sizeof(t_registered_event))) == NULL)
		exit_program(doom, ERROR_SDL_AFTER_INIT);
	event->type = type;
	event->handler = handler;
	event->gamemode = doom->game_mode;
	lstcontainer_add(doom->events, event);
}
