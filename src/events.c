/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 17:45:39 by lde-batz          #+#    #+#             */
/*   Updated: 2019/05/06 15:19:19 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		mouse_movement(t_doom *doom, SDL_Event event)
{
	SDL_MouseMotionEvent mouse;

	mouse = event.motion;
	if (doom->mouse_focused)
	{
		turn(mouse.xrel * -doom->settings.mouse_sensitivity, &doom->you);
		doom->you.pitch += mouse.yrel * -doom->settings.mouse_sensitivity;
		if (doom->you.pitch < 0)
			doom->you.pitch = 0;
		if (doom->you.pitch > 1)
			doom->you.pitch = 1;
	}
	return (1);
}

void	turn(double angle, t_player *player)
{
	double		old_dir_x;
	double		old_plane_x;

	player->angle = atan2(player->dir.y, player->dir.x);
	player->anglecos = cos(player->angle);
	player->anglesin = sin(player->angle);
	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * cos(angle) - player->dir.y * sin(angle);
	player->dir.y = old_dir_x * sin(angle) + player->dir.y * cos(angle);
	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x * cos(angle)
		- player->plane.y * sin(angle);
	player->plane.y = old_plane_x * sin(angle) + player->plane.y * cos(angle);
}

int		key_down(t_doom *doom, SDL_Event event)
{
	SDL_KeyboardEvent keyb;

	keyb = event.key;
	if (keyb.keysym.scancode == doom->settings.key_forward)
		doom->keys.up = 1;
	if (keyb.keysym.scancode == doom->settings.key_backward)
		doom->keys.down = 1;
	if (keyb.keysym.scancode == doom->settings.key_left)
		doom->keys.left = 1;
	if (keyb.keysym.scancode == doom->settings.key_right)
		doom->keys.right = 1;
	if (keyb.keysym.scancode == doom->settings.key_sprint)
		doom->you.is_sprinting = 1;
	if (keyb.keysym.scancode == doom->settings.key_crouch)
		doom->you.is_crouching = 1;
	if (keyb.keysym.scancode == SDL_SCANCODE_ESCAPE)
		exit_program(doom, 0);
	return (1);
}

void	key_up2(t_doom *doom, SDL_KeyboardEvent *keyb)
{
	if (keyb->keysym.scancode == SDL_SCANCODE_F9)
	{
		SDL_SetRelativeMouseMode(!doom->mouse_focused);
		SDL_WarpMouseInWindow(doom->win, WIN_W / 2, WIN_H / 2);
		doom->mouse_focused = !doom->mouse_focused;
	}
	if (keyb->keysym.scancode == SDL_SCANCODE_TAB && doom->editor.anim_finished)
		switch_to_editor(doom);
}

int		key_up(t_doom *doom, SDL_Event event)
{
	SDL_KeyboardEvent keyb;

	keyb = event.key;
	if (keyb.keysym.scancode == doom->settings.key_forward)
		doom->keys.up = 0;
	if (keyb.keysym.scancode == doom->settings.key_backward)
		doom->keys.down = 0;
	if (keyb.keysym.scancode == doom->settings.key_left)
		doom->keys.left = 0;
	if (keyb.keysym.scancode == doom->settings.key_right)
		doom->keys.right = 0;
	if (keyb.keysym.scancode == doom->settings.key_sprint)
		doom->you.is_sprinting = 0;
	if (keyb.keysym.scancode == doom->settings.key_crouch)
		doom->you.is_crouching = 0;
	if (keyb.keysym.scancode == SDL_SCANCODE_F9)
	{
		SDL_SetRelativeMouseMode(!doom->mouse_focused);
		SDL_WarpMouseInWindow(doom->win, WIN_W / 2, WIN_H / 2);
		doom->mouse_focused = !doom->mouse_focused;
	}
	if (keyb.keysym.scancode == SDL_SCANCODE_TAB && doom->editor.anim_finished)
		switch_to_editor(doom);
//	key_up2(doom, &keyb);
	return (1);
}
