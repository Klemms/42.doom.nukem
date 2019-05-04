/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 10:12:00 by lde-batz          #+#    #+#             */
/*   Updated: 2019/05/02 18:12:21 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

#include "doom.h"

int				mouse_movement(t_doom *doom, SDL_Event event)
{
	SDL_MouseMotionEvent mouse;

	mouse = event.motion;
	if (doom->mouse_focused)
		turn(mouse.xrel * -doom->settings.mouse_sensitivity, &doom->you);
	return (1);
}

int				key_down(t_doom *doom, SDL_Event event)
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
	if (keyb.keysym.scancode == doom->settings.z_up)
		doom->keys.z_up = 1;
	if (keyb.keysym.scancode == doom->settings.z_down)
		doom->keys.z_down = 1;
	if (keyb.keysym.scancode == SDL_SCANCODE_ESCAPE)
		exit_program(doom, 0);
	return (1);
}

int				key_up(t_doom *doom, SDL_Event event)
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
		doom->you.is_crouching = 1;
	if (keyb.keysym.scancode == doom->settings.z_up)
		doom->keys.z_up = 0;
	if (keyb.keysym.scancode == doom->settings.z_down)
		doom->keys.z_down = 0;
	if (keyb.keysym.scancode == SDL_SCANCODE_F9)
	{
		SDL_SetRelativeMouseMode(!doom->mouse_focused);
		SDL_WarpMouseInWindow(doom->win, WIN_W / 2, WIN_H / 2);
		doom->mouse_focused = !doom->mouse_focused;
	}
	if (keyb.keysym.scancode == SDL_SCANCODE_TAB && doom->editor.anim_finished)
		switch_to_editor(doom);
	return (1);
}

void		turn(double angle, t_player *player)
{
	double		old_dir_x;
	double		old_plane_x;

	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * cos(angle) - player->dir.y * sin(angle);
	player->dir.y = old_dir_x * sin(angle) + player->dir.y * cos(angle);
	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x * cos(angle) - player->plane.y * sin(angle);
	player->plane.y = old_plane_x * sin(angle) + player->plane.y * cos(angle);
}

void		moove(double dist, t_player *player, t_map *map, double angle)
{
	double		tmp_dir_x;
	double		vx;
	double		vy;
	double		next_y;
	double		next_x;

	double tvx;
	double tvy;

	if (angle != 0)
	{
		vx = (player->dir.x * cos(angle) - player->dir.y * sin(angle));// * dist;
		vy = (player->dir.x * sin(angle) + player->dir.y * cos(angle));// * dist;
	}
	else
	{
		vx = player->dir.x;// * dist;
		vy = player->dir.y;
	}
	
	tvx = player->pos.x + vx * (dist * 1.1);
	tvy = player->pos.y + vy * (dist * 1.1);
	vx *= dist;
	vy *= dist;
	next_x = player->pos.x + vx;
	next_y = player->pos.y + vy;
	if (next_x < map->width && next_x >= 0
	&& next_y < map->height && next_y > 0)
	{
		//if (map->m[(int)(next_y)][(int)(next_x)] == '.')
		//{
			if (map->m[(int)player->pos.y][(int)(tvx)] == '.')
				player->pos.x = next_x;
			if (map->m[(int)(tvy)][(int)player->pos.x] == '.')
				player->pos.y = next_y;
			if (player->pos.x == next_x && player->pos.y == next_y)
				if (map->m[(int)(tvy)][(int)(tvx)] != '.')
				{
					player->pos.x -= vx;
					player->pos.y -= vy;
				}
		//}
		if (player->pos.y != next_y && player->pos.x == next_x)
			player->pos.x -= (vx / 2);
		else if (player->pos.x != next_x && player->pos.y == next_y)
			player->pos.y -= (vy / 2);
	}
}