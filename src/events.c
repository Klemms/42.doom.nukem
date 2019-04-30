/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 14:51:35 by hdussert          #+#    #+#             */
/*   Updated: 2019/04/30 17:01:56 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int				key_down(t_doom *doom, SDL_Event event)
{
	SDL_KeyboardEvent keyb;

	keyb = event.key;
	printf("scancode: %d\n", keyb.keysym.scancode);
	fflush(stdout);
	if (keyb.keysym.scancode == SDL_SCANCODE_RIGHT)
		doom->keys.left = 1;
	if (keyb.keysym.scancode == SDL_SCANCODE_LEFT)
		doom->keys.right = 1;
	if (keyb.keysym.scancode == SDL_SCANCODE_UP)
		doom->keys.up = 1;
	if (keyb.keysym.scancode == SDL_SCANCODE_DOWN)
		doom->keys.down = 1;
	if (keyb.keysym.scancode == SDL_SCANCODE_S)
		doom->keys.shadow = !doom->keys.shadow;
	if (keyb.keysym.scancode == SDL_SCANCODE_J)
		doom->you.rov += (doom->you.rov + 1 < 30);
	if (keyb.keysym.scancode == SDL_SCANCODE_K)
		doom->you.rov -= (doom->you.rov - 1 > 8);
	if (keyb.keysym.scancode == SDL_SCANCODE_ESCAPE)
		exit_program(doom, 0);
	return (1);
}

int				key_up(t_doom *doom, SDL_Event event)
{
	SDL_KeyboardEvent keyb;

	keyb = event.key;
	if (keyb.keysym.scancode == SDL_SCANCODE_RIGHT)
		doom->keys.left = 0;
	if (keyb.keysym.scancode == SDL_SCANCODE_LEFT)
		doom->keys.right = 0;
	if (keyb.keysym.scancode == SDL_SCANCODE_UP)
		doom->keys.up = 0;
	if (keyb.keysym.scancode == SDL_SCANCODE_DOWN)
		doom->keys.down = 0;
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

void		moove(double dist, t_player *player, t_map *map, int ang)
{
	double		tmp_dir_x;
	double		vx;
	double		vy;
	double		next_y;
	double		next_x;

	if (ang == 0)
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
	}
	next_x = player->pos.x + vx;
	next_y = player->pos.y + vy;
	if (next_x < map->width && next_x >= 0
	&& next_y < map->height && next_y > 0)
	{
		if (map->m[(int)player->pos.y][(int)(next_x)] != '#')
			player->pos.x = next_x;
		if (map->m[(int)(next_y)][(int)player->pos.x] != '#')
			player->pos.y = next_y;
		if (player->pos.x == next_x && player->pos.y != next_y)
			player->pos.x -= (vx / 2);
		else if (player->pos.x != next_x && player->pos.y == next_y)
			player->pos.y -= (vy / 2);
	}
}
