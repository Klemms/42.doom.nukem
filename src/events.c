/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 14:51:35 by hdussert          #+#    #+#             */
/*   Updated: 2019/02/22 15:06:14 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				key_down(int key, t_wolf *w)
{
	if (key == 123)
		w->keys->left = 1;
	if (key == 124)
		w->keys->right = 1;
	if (key == 126)
		w->keys->up = 1;
	if (key == 125)
		w->keys->down = 1;
	if (key == 1)
		w->keys->shadow = !w->keys->shadow;
	if (key == 41)
		w->you->rov += (w->you->rov + 1 < 30);
	if (key == 39)
		w->you->rov -= (w->you->rov - 1 > 8);
	if (key == 53)
		exit_program(w, 0);
	return (key);
}

int				key_up(int key, t_wolf *w)
{
	if (key == 123)
		w->keys->left = 0;
	if (key == 124)
		w->keys->right = 0;
	if (key == 126)
		w->keys->up = 0;
	if (key == 125)
		w->keys->down = 0;
	return (key);
}

static void		turn(double angle, t_player *you)
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

static void		moove(double dist, t_player *you, t_map *map)
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

int				loop(t_wolf *w)
{
	if (w->keys->right == 1)
		turn(-w->you->rotspeed, w->you);
	if (w->keys->left == 1)
		turn(w->you->rotspeed, w->you);
	if (w->keys->up == 1)
		moove(w->you->speed, w->you, w->map);
	if (w->keys->down == 1)
		moove(-w->you->speed, w->you, w->map);
	draw(w);
	return (0);
}
