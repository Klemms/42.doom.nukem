/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fade.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 05:06:45 by cababou           #+#    #+#             */
/*   Updated: 2019/05/06 15:56:56 by lde-batz         ###   ########.fr       */
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
	r = make_rect(WIN_W / 2 - new_w, WIN_H / 2 - new_h, doom->editor.anim_w,
														doom->editor.anim_h);
	SDL_SetSurfaceAlphaMod(doom->editor.ed_surface, doom->editor.anim_alpha);
	SDL_BlitScaled(doom->editor.ed_surface, NULL, doom->surface, &r);
	doom->editor.anim_w *= 0.9;
	doom->editor.anim_h *= 0.9;
	doom->editor.anim_alpha *= 0.6;
	if (doom->editor.anim_w <= WIN_W / 2)
		doom->editor.anim_finished = 1;
}

void	fade_surface_back(t_doom *doom)
{
	SDL_Rect	r;
	int			new_w;
	int			new_h;

	new_w = doom->editor.anim_w * 1.15;
	new_h = doom->editor.anim_h * 1.15;
	r = make_rect(WIN_W / 2 - new_w / 2, WIN_H / 2 - new_h / 2, new_w, new_h);
	SDL_SetSurfaceAlphaMod(doom->editor.ed_surface, doom->editor.anim_alpha);
	SDL_BlitScaled(doom->editor.ed_surface, NULL, doom->surface, &r);
	doom->editor.anim_w *= 1.15;
	doom->editor.anim_h *= 1.15;
	if (doom->editor.anim_alpha + 35 > 255)
		doom->editor.anim_alpha = 255;
	else
		doom->editor.anim_alpha += 20;
	if (doom->editor.anim_w >= WIN_W || doom->editor.anim_h >= WIN_H)
	{
		SDL_SetSurfaceAlphaMod(doom->editor.ed_surface, 255);
		doom->editor.anim_finished = 1;
	}
}
