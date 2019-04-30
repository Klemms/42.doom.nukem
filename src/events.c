/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 14:51:35 by hdussert          #+#    #+#             */
/*   Updated: 2019/04/30 16:38:19 by cababou          ###   ########.fr       */
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
		doom->keys->left = 1;
	if (keyb.keysym.scancode == SDL_SCANCODE_LEFT)
		doom->keys->right = 1;
	if (keyb.keysym.scancode == SDL_SCANCODE_UP)
		doom->keys->up = 1;
	if (keyb.keysym.scancode == SDL_SCANCODE_DOWN)
		doom->keys->down = 1;
	if (keyb.keysym.scancode == SDL_SCANCODE_S)
		doom->keys->shadow = !doom->keys->shadow;
	if (keyb.keysym.scancode == SDL_SCANCODE_J)
		doom->you->rov += (doom->you->rov + 1 < 30);
	if (keyb.keysym.scancode == SDL_SCANCODE_K)
		doom->you->rov -= (doom->you->rov - 1 > 8);
	if (keyb.keysym.scancode == SDL_SCANCODE_ESCAPE)
		exit_program(doom, 0);
	return (1);
}

int				key_up(t_doom *doom, SDL_Event event)
{
	SDL_KeyboardEvent keyb;

	keyb = event.key;
	if (keyb.keysym.scancode == SDL_SCANCODE_RIGHT)
		doom->keys->left = 0;
	if (keyb.keysym.scancode == SDL_SCANCODE_LEFT)
		doom->keys->right = 0;
	if (keyb.keysym.scancode == SDL_SCANCODE_UP)
		doom->keys->up = 0;
	if (keyb.keysym.scancode == SDL_SCANCODE_DOWN)
		doom->keys->down = 0;
	return (1);
}

void		turn(double angle, t_player *you)
{
	double		old_dir_x;
	double		old_plane_x;

	old_dir_x = you->dir->x;
	you->dir->x = you->dir->x * cos(angle) - you->dir->y * sin(angle);
	you->dir->y = old_dir_x * sin(angle) + you->dir->y * cos(angle);
	old_plane_x = you->plane->x;
	you->plane->x = you->plane->x * cos(angle) - you->plane->y * sin(angle);
	you->plane->y = old_plane_x * sin(angle) + you->plane->y * cos(angle);
}

void		moove(double dist, t_player *you, t_map *map)
{
	double		vx;
	double		vy;
	double		next_y;
	double		next_x;

	vx = you->dir->x * dist;
	vy = you->dir->y * dist;
	next_x = you->pos->x + vx;
	next_y = you->pos->y + vy;
	if (next_x < map->width && next_x >= 0
	&& next_y < map->height && next_y > 0)
	{
		if (map->m[(int)you->pos->y][(int)(next_x)] != '#')
			you->pos->x = next_x;
		if (map->m[(int)(next_y)][(int)you->pos->x] != '#')
			you->pos->y = next_y;
		if (you->pos->x == next_x && you->pos->y != next_y)
			you->pos->x -= (vx / 2);
		else if (you->pos->x != next_x && you->pos->y == next_y)
			you->pos->y -= (vy / 2);
	}
}
