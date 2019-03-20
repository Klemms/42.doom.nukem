/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:29:49 by cababou           #+#    #+#             */
/*   Updated: 2019/03/19 16:30:05 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	init_events(t_wolf *wolf)
{
	if ((wolf->events = lstcontainer_new()) == NULL)
		exit_program(ERROR_MEMORY);
}

void	distribute_events(t_wolf *wolf, SDL_Event sdl_event)
{
	t_list				*list;
	t_registered_event	*event;

	list = wolf->events->firstelement;
	while (list)
	{
		event = (t_registered_event *)list;
		if (event->type == sdl_event.type)
		{
			event->handler(wolf, sdl_event);
		}
	}
}

void	register_event(t_wolf *wolf, Uint32 type,
			int (*handler)(t_wolf *w, SDL_Event ev))
{
	t_registered_event	*event;

	if ((event = malloc(sizeof(t_registered_event))) == NULL)
		exit_program(ERROR_MEMORY);
	event->type = type;
	event->handler = handler;
	lstcontainer_add(wolf->events, event);
}