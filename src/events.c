/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 14:51:35 by hdussert          #+#    #+#             */
/*   Updated: 2019/04/30 16:30:06 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int				key_down(int key, t_doom *doom)
{
	if (key == 123)
		doom->keys.left = 1;
	if (key == 124)
		doom->keys.right = 1;
	if (key == 13)
		doom->keys.w = 1;
	if (key == 1)
		doom->keys.s = 1;
	if (key == 0)
		doom->keys.a = 1;
	if (key == 2)
		doom->keys.d = 1;
	if (key == 41)
		doom->you.rov += (doom->you.rov + 1 < 30);
	if (key == 39)
		doom->you.rov -= (doom->you.rov - 1 > 8);
	if (key == 53)
		exit_program(doom, 0);
	return (key);
}

int				key_up(int key, t_doom *doom)
{
	if (key == 123)
		doom->keys.left = 0;
	if (key == 124)
		doom->keys.right = 0;
	if (key == 13)
		doom->keys.w = 0;
	if (key == 1)
		doom->keys.s = 0;
	if (key == 0)
		doom->keys.a = 0;
	if (key == 2)
		doom->keys.d = 0;
	return (key);
}

static void		turn(double angle, t_player *you)
{
	double		old_dir_x;
	double		old_plane_x;

	old_dir_x = you->dir.x;
	you->dir.x = you->dir.x * cos(angle) - you->dir.y * sin(angle);
	you->dir.y = old_dir_x * sin(angle) + you->dir.y * cos(angle);
	old_plane_x = you->plane.x;
	you->plane.x = you->plane.x * cos(angle) - you->plane.y * sin(angle);
	you->plane.y = old_plane_x * sin(angle) + you->plane.y * cos(angle);
}

static void		moove(double dist, t_player *you, t_map *map, int ang)
{
	double		tmp_dir_x;
	double		vx;
	double		vy;
	double		next_y;
	double		next_x;

	if (ang == 0)
	{
		printf("w ou s\n");
		vx = you->dir.x * dist;
		vy = you->dir.y * dist;
	}
	else
	{
		printf("a ou d\n");
		tmp_dir_x = you->dir.x;
		vx = (you->dir.x * cos(M_PI_2 * ang) - you->dir.y * sin(M_PI_2 * ang)) * dist;
		vy = (tmp_dir_x * sin(M_PI_2 * ang) + you->dir.y * cos(M_PI_2 * ang)) * dist;
	}
	next_x = you->pos.x + vx;
	next_y = you->pos.y + vy;
	if (next_x < map->width && next_x >= 0
	&& next_y < map->height && next_y > 0)
	{
		if (map->m[(int)you->pos.y][(int)(next_x)] != '#')
			you->pos.x = next_x;
		if (map->m[(int)(next_y)][(int)you->pos.x] != '#')
			you->pos.y = next_y;
		if (you->pos.x == next_x && you->pos.y != next_y)
			you->pos.x -= (vx / 2);
		else if (you->pos.x != next_x && you->pos.y == next_y)
			you->pos.y -= (vy / 2);
	}
}

int				loop(t_doom *doom)
{
	double	dir[2];
	int		push;
	double	acc;

	dir[0] = 0.0;
	dir[1] = 0.0;
	doom->map.width = 13;
	if (doom->keys.right == 1)
		turn(-doom->you.rotspeed, &doom->you);
	if (doom->keys.left == 1)
		turn(doom->you.rotspeed, &doom->you);
	if (doom->keys.w == 1)
	{
		dir[0] += doom->you.anglecos * 0.2f;
		dir[1] += doom->you.anglesin * 0.2f;
	}
	if (doom->keys.s == 1)
	{
		dir[0] -= doom->you.anglecos * 0.2f;
		dir[1] -= doom->you.anglesin * 0.2f;
	}
	if (doom->keys.a == 1)
	{
		dir[0] += doom->you.anglesin * 0.2f;
		dir[1] -= doom->you.anglecos * 0.2f;
	}
	if (doom->keys.d == 1)
	{
		dir[0] -= doom->you.anglesin * 0.2f;
		dir[1] += doom->you.anglecos * 0.2f;
	}
	push = doom->keys.w || doom->keys.s || doom->keys.a || doom->keys.d;
	acc = push ? 0.4 : 0.2;
	doom.velocity.x = player.velocity.x * (1-acceleration) + move_vec[0] * acceleration;
    player.velocity.y = player.velocity.y * (1-acceleration) + move_vec[1] * acceleration;
//	if (doom->keys.w == 1)
//		moove(doom->you.speed, &doom->you, &doom->map, 0);
//	if (doom->keys.s == 1)
//		moove(-doom->you.speed, &doom->you, &doom->map, 0);
//	if (doom->keys.a == 1)
//		moove(doom->you.speed, &doom->you, &doom->map, 1);
//	if (doom->keys.d == 1)
//		moove(doom->you.speed, &doom->you, &doom->map, -1);
	printf("velocity: %f %f\n", doom->you.dir.x, doom->you.dir.y);
	draw(doom);
	return (0);
}
