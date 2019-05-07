/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_clicks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 23:07:12 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 20:48:11 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "editor.h"

void	ed_none_c(t_doom *doom, t_el_button *b, SDL_MouseButtonEvent ev)
{
	(void)b;
	if (ev.button == SDL_BUTTON_LEFT)
	{
		switch_tool(doom, tool_none, NULL);
	}
}

void	ed_block_c(t_doom *doom, t_el_button *b, SDL_MouseButtonEvent ev)
{
	(void)b;
	if (ev.button == SDL_BUTTON_LEFT)
	{
		switch_tool(doom, tool_block, NULL);
	}
}

void	ed_sprite_c(t_doom *doom, t_el_button *b, SDL_MouseButtonEvent ev)
{
	(void)b;
	if (ev.button == SDL_BUTTON_LEFT)
	{
		switch_tool(doom, tool_sprite, NULL);
	}
}
