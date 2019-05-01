/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fade.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 05:06:45 by cababou           #+#    #+#             */
/*   Updated: 2019/05/01 07:26:28 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	fade_surface(t_doom *doom)
{
	SDL_Rect	r;
	int			new_w;
	int			new_h;

	new_w = doom->editor.anim_w / 2;
	new_h = doom->editor.anim_h / 2;
	r = make_rect(doom->settings.window_width / 2 - new_w, doom->settings.window_height / 2 - new_h, doom->editor.anim_w, doom->editor.anim_h);
	SDL_SetSurfaceAlphaMod(doom->editor.ed_surface, doom->editor.anim_alpha);
	SDL_BlitScaled(doom->editor.ed_surface, NULL, doom->surface, &r);
	doom->editor.anim_w *= 0.9;
	doom->editor.anim_h *= 0.9;
	doom->editor.anim_alpha *= 0.6;
	if (doom->editor.anim_w <= doom->settings.window_width / 2)
		doom->editor.anim_finished = 1;
}

void	fade_surface_back(t_doom *doom)
{
	SDL_Rect	r;
	int			new_w;
	int			new_h;

	new_w = doom->editor.anim_w * 1.1;
	new_h = doom->editor.anim_h * 1.1;
	r = make_rect(doom->settings.window_width / 2 - new_w / 2, doom->settings.window_height / 2 - new_h / 2, new_w, new_h);
	SDL_SetSurfaceAlphaMod(doom->editor.ed_surface, doom->editor.anim_alpha);
	SDL_BlitScaled(doom->editor.ed_surface, NULL, doom->surface, &r);
	doom->editor.anim_w *= 1.15;
	doom->editor.anim_h *= 1.15;
	if (doom->editor.anim_alpha + 35 > 255)
		doom->editor.anim_alpha = 255;
	else
		doom->editor.anim_alpha += 20;
	if (doom->editor.anim_w >= doom->settings.window_width || doom->editor.anim_h >= doom->settings.window_height)
	{
		SDL_SetSurfaceAlphaMod(doom->editor.ed_surface, 255);
		doom->editor.anim_finished = 1;
	}
}