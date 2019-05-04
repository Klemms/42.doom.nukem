/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 10:12:00 by lde-batz          #+#    #+#             */
/*   Updated: 2019/05/03 19:13:09 by lde-batz         ###   ########.fr       */
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

void	moving2(t_doom *doom)
{
	double		old_dir_x;
	double		old_plane_x;

	if (doom->you.moving)
	{
		channel = Mix_PlayChannel(-1, doom->scores.walk, 0);
		if (channel != 0)
			Mix_HaltChannel(channel);
	}
	collision.x = (doom->you.velocity.x < 0) ? doom->you.velocity.x - COL : doom->you.velocity.x + COL;
	collision.y = (doom->you.velocity.y < 0) ? doom->you.velocity.y - COL : doom->you.velocity.y + COL;
	tmp_pos_x = doom->you.pos.x;
	dest[0] = doom->you.pos.x + collision.x;
	dest[1] = doom->you.pos.y + collision.y;
	if (doom->map.m[(int)doom->you.pos.y][dest[0]] != '.')
	{
		if (doom->you.velocity.x < 0)
			doom->you.pos.x = dest[0] + 1 + COL;
		else
			doom->you.pos.x = dest[0] - COL;
	}
	else
	{
		if (doom->you.velocity.y < 0)
			doom->you.pos.y = dest[1] + 1 + COL;
		else
			doom->you.pos.y = dest[1] - COL;
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

int		check_collision(t_doom *doom, int neighbors[2])
{
	if (doom->map.m[neighbors[1]][neighbors[0]] != '.')
		return (1);
	return (0);
}

void	moving(t_doom *doom)
{
	t_xy	dest;
	int channel;
	int	neighbors[2];
	int	tmp_neighbors;
	
	if (doom->you.moving)
	{
		channel = Mix_PlayChannel(-1, doom->scores.walk, 0);
		if (channel != 0)
			Mix_HaltChannel(channel);
	}
	dest.x = doom->you.pos.x + doom->you.velocity.x;
	dest.y = doom->you.pos.y + doom->you.velocity.y;
	if ((int)dest.x != (int)doom->you.pos.x && (int)dest.y != (int)doom->you.pos.y)
	{
		;
//		printf("1\n");
//		doom->you.velocity.x = 0;
//		doom->you.velocity.y = 0;
	}
	else if ((int)dest.x != (int)doom->you.pos.x || (int)dest.y != (int)doom->you.pos.y)
	{
//		printf("2\n");
		if ((int)dest.x != (int)doom->you.pos.x)
		{
			if (dest.y - (int)doom->you.pos.y <= COL || dest.y - (int)doom->you.pos.y >= 1 - COL)
			{
				neighbors[0] = (int)doom->you.pos.x;
				if (dest.y - (int)doom->you.pos.y <= COL)
					neighbors[1] = (int)doom->you.pos.y - 1;
				else
					neighbors[1] = (int)doom->you.pos.y + 1;
				if (check_collision(doom, neighbors))
					doom->you.velocity.y = 0;
			}
		}
		if ((int)dest.y != (int)doom->you.pos.y)
		{
			if (dest.x - (int)doom->you.pos.x <= COL || dest.x - (int)doom->you.pos.x >= 1 - COL)
			{
				if (dest.x - (int)doom->you.pos.x <= COL)
					neighbors[0] = (int)doom->you.pos.x - 1;
				else
					neighbors[0] = (int)doom->you.pos.x + 1;
				neighbors[1] = (int)doom->you.pos.y;
				if (check_collision(doom, neighbors))
					doom->you.velocity.x = 0;
			}
		}
	}
	else if ((dest.x - (int)doom->you.pos.x <= COL || dest.x - (int)doom->you.pos.x >= 1 - COL)
	&& (dest.y - (int)doom->you.pos.y <= COL || dest.y - (int)doom->you.pos.y >= 1 - COL))
	{
//		printf("3\n");
		if (dest.x - (int)doom->you.pos.x <= COL)
			neighbors[0] = (int)doom->you.pos.x - 1;
		else
			neighbors[0] = (int)doom->you.pos.x + 1;
		neighbors[1] = (int)doom->you.pos.y;
		if (check_collision(doom, neighbors))
			doom->you.velocity.x = 0;
		tmp_neighbors = neighbors[0];
		neighbors[0] = (int)doom->you.pos.x;
		if (dest.y - (int)doom->you.pos.y <= COL)
			neighbors[1] = (int)doom->you.pos.y - 1;
		else
			neighbors[1] = (int)doom->you.pos.y + 1;
		if (check_collision(doom, neighbors))
			doom->you.velocity.y = 0;
		neighbors[0] = tmp_neighbors;
		if (check_collision(doom, neighbors) && doom->you.velocity.x != 0 && doom->you.velocity.y != 0)
		{
			if (fabs(round(dest.x) - dest.x) > fabs(round(dest.y) - dest.y))
				doom->you.velocity.x = 0;
			else
				doom->you.velocity.y = 0;
		}
	}
	else if (dest.x - (int)doom->you.pos.x <= COL || dest.x - (int)doom->you.pos.x >= 1 - COL)
	{
//		printf("4\n");
		if (dest.x - (int)doom->you.pos.x <= COL)
			neighbors[0] = (int)doom->you.pos.x - 1;
		else
			neighbors[0] = (int)doom->you.pos.x + 1;
		neighbors[1] = (int)doom->you.pos.y;
		if (check_collision(doom, neighbors))
			doom->you.velocity.x = 0;
	}
	else if (dest.y - (int)doom->you.pos.y <= COL || dest.y - (int)doom->you.pos.y >= 1 - COL)
	{
//		printf("5\n");
		neighbors[0] = (int)doom->you.pos.x;
		if (dest.y - (int)doom->you.pos.y <= COL)
			neighbors[1] = (int)doom->you.pos.y - 1;
		else
			neighbors[1] = (int)doom->you.pos.y + 1;
		if (check_collision(doom, neighbors))
			doom->you.velocity.y = 0;
	}
	doom->you.pos.x += doom->you.velocity.x;
	doom->you.pos.y += doom->you.velocity.y;	
}
