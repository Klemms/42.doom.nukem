/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 14:51:35 by hdussert          #+#    #+#             */
/*   Updated: 2019/05/03 02:33:35 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int				mouse_movement(t_doom *doom, SDL_Event event)
{
	SDL_MouseMotionEvent mouse;

	mouse = event.motion;
	if (doom->mouse_focused)
		turn(mouse.xrel * -doom->settings.mouse_sensitivity, &doom->you, doom);
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

void		turn(double angle, t_player *player, t_doom *doom)
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
	player->plane.x = player->plane.x * cos(angle) - player->plane.y * sin(angle);
	player->plane.y = old_plane_x * sin(angle) + player->plane.y * cos(angle);
}

void		moove(double dist, t_doom *doom, t_map *map, int ang)
{
	double		tmp_dir_x;
	double		vx;
	double		vy;
	double		next_y;
	double		next_x;
	int			channel;

	channel = Mix_PlayChannel(-1, doom->scores.walk, 0);
	if (channel != 0)
		Mix_HaltChannel(channel);
	vx = doom->you.dir.x * dist;
	vy = doom->you.dir.y * dist;
	/*if (ang == 0)
	{
		printf("w ou s\n");
		vx = player->dir.x * dist;
		vy = player->dir.y * dist;
	}
	else
	{
		printf("a ou d\n");
		tmp_dir_x = player->dir.x;
		vx = (player->dir.x * cos(M_PI_2 * ang) - player->dir.y * sin(M_PI_2 * ang)) * dist;
		vy = (tmp_dir_x * sin(M_PI_2 * ang) + player->dir.y * cos(M_PI_2 * ang)) * dist;
	}*/
	next_x = doom->you.pos.x + vx;
	next_y = doom->you.pos.y + vy;
	if (next_x < map->width && next_x >= 0
	&& next_y < map->height && next_y > 0)
	{
		if (map->m[(int)doom->you.pos.y][(int)(next_x)] != '#' && map->m[(int)doom->you.pos.y][(int)(next_x)] != 'C')
			doom->you.pos.x = next_x;
		if (map->m[(int)(next_y)][(int)doom->you.pos.x] != '#' && map->m[(int)(next_y)][(int)doom->you.pos.x] != 'C')
			doom->you.pos.y = next_y;
		if (doom->you.pos.x == next_x && doom->you.pos.y != next_y)
			doom->you.pos.x -= (vx / 2);
		else if (doom->you.pos.x != next_x && doom->you.pos.y == next_y)
			doom->you.pos.y -= (vy / 2);
	}
}
