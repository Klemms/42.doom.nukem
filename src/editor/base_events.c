/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 04:16:03 by cababou           #+#    #+#             */
/*   Updated: 2019/05/03 01:44:20 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "editor.h"

int		ed_mouse_motion(t_doom *doom, SDL_Event sdl_event)
{
	SDL_MouseMotionEvent	motion;
	int					m_x;
	int					m_y;

	SDL_GetMouseState(&m_x, &m_y);
	motion = sdl_event.motion;
	if (mouse_in(m_x, m_y, doom->editor.flat_top_render_rect) && doom->editor.wheel_pressed)
	{
		doom->editor.flat_top_quadrant.x_start += motion.xrel;
		doom->editor.flat_top_quadrant.y_start += motion.yrel;
	}
	return (1);
}

int		ed_mouse_button(t_doom *doom, SDL_Event sdl_event)
{
	SDL_MouseButtonEvent	mouse;
	t_editor				*e;

	e = &doom->editor;
	mouse = sdl_event.button;
	if (mouse.button == SDL_BUTTON_MIDDLE)
	{
		if (mouse.state == SDL_PRESSED)
			doom->editor.wheel_pressed = 1;
		else
			doom->editor.wheel_pressed = 0;
	}
	if (mouse.button == SDL_BUTTON_LEFT)
	{
		if (e->c_focus == 1 && e->x_focus >= 0 && e->y_focus >= 0)
			editor_ftr_clicked(doom);
	}
	return (0);
}

int		zoom_event(t_doom *doom, SDL_Event sdl_event)
{
	SDL_MouseWheelEvent	wheel;
	int					m_x;
	int					m_y;

	SDL_GetMouseState(&m_x, &m_y);
	wheel = sdl_event.wheel;
	if (mouse_in(m_x, m_y, doom->editor.flat_top_render_rect))
		doom->editor.flat_top_quadrant.zoom_level += wheel.y > 0 ? 1 : -1;
	if (doom->editor.flat_top_quadrant.zoom_level <= 0)
		doom->editor.flat_top_quadrant.zoom_level = 1;
	return (1);
}

int		quit_event(t_doom *doom, SDL_Event sdl_event)
{
	exit_program(doom, 0);
	return (0);
}

int		key_event(t_doom *doom, SDL_Event sdl_event)
{
	if (sdl_event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		exit_program(doom, 0);
	if (sdl_event.key.keysym.scancode == SDL_SCANCODE_TAB && doom->editor.anim_finished)
		switch_to_game(doom);
	if (sdl_event.key.keysym.scancode == SDL_SCANCODE_1)
		switch_tool(doom, tool_none);
	if (sdl_event.key.keysym.scancode == SDL_SCANCODE_2)
		switch_tool(doom, tool_block);
	return (0);
}