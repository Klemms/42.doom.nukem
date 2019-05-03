/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 04:50:07 by cababou           #+#    #+#             */
/*   Updated: 2019/05/03 08:08:04 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	switch_to_game(t_doom *doom)
{
	if (doom->game_mode == M_EDITOR)
	{
		doom->game_mode = M_GAME;
		doom->editor.anim_w = WIN_W;
		doom->editor.anim_h = WIN_H;
		doom->editor.anim_alpha = 255;
		doom->editor.anim_finished = 0;
		SDL_SetRelativeMouseMode(SDL_TRUE);
		doom->mouse_focused = 1;
		if (!doom->game_init)
			init_game(doom);
	}
}

void	switch_to_editor(t_doom *doom)
{
	if (doom->game_mode == M_GAME)
	{
		SDL_SetRelativeMouseMode(SDL_FALSE);
		doom->mouse_focused = 0;
		doom->game_mode = M_EDITOR;
		doom->editor.anim_w = WIN_W / 4;
		doom->editor.anim_h = WIN_H / 4;
		doom->editor.anim_alpha = 1;
		doom->editor.anim_finished = 0;
	}
}
