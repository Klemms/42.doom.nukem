/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 19:15:11 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 20:14:17 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_hud(t_doom *d)
{
	t_texture	*tmp;

	tmp = load_texture(d, ft_strdup("textures/gun1.png"));
	d->you.hud.gun_1 = tmp ? tmp->surface : NULL;
	free(tmp);
	tmp = load_texture(d, ft_strdup("textures/gun3.png"));
	d->you.hud.gun_3 = tmp ? tmp->surface : NULL;
	free(tmp);
	tmp = load_texture(d, ft_strdup("textures/key_hud.png"));
	d->you.hud.key_h = tmp ? tmp->surface : NULL;
	free(tmp);
	tmp = load_texture(d, ft_strdup("textures/ammo.png"));
	d->you.hud.ammo_tt = tmp ? tmp->surface : NULL;
	free(tmp);
}

void	render_hud(t_doom *d)
{
	SDL_Rect	r;

	r = make_rect(WIN_W / 2 - 400, WIN_H - 800, 800, 800);
	SDL_BlitScaled(d->you.hud.gun_1, NULL, d->surface, &r);
	r = make_rect(50, 100, 60, 40);
	SDL_BlitScaled(d->you.hud.key_h, NULL, d->surface, &r);
	d->tmp_color = make_rgb(255, 255, 255, 255);
	instant_text(d, d->surface, ft_itoa(d->you.hud.key), make_rect(125, 100, 30, 0));
	draw_rect_u(d->surface, make_rect(55, WIN_H - 100, 400, 45), 0xFF888888, 1);
	draw_rect_u(d->surface, make_rect(55, WIN_H - 100,
			((float)d->you.hud.health) / 100.0 * 400, 45), 0xFFFF2222, 1);
	instant_text(d, d->surface, ft_itoa(d->you.hud.health), make_rect(225, WIN_H - 95, 30, 0));
	r = make_rect(WIN_W - 450, WIN_H - 630, 600, 600);
	SDL_BlitScaled(d->you.hud.ammo_tt, NULL, d->surface, &r);
	instant_text(d, d->surface, ft_itoa(d->you.hud.ammo), make_rect(WIN_W - 250, WIN_H - 130, 40, 0));
}