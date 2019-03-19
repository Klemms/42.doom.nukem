/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:12:03 by lde-batz          #+#    #+#             */
/*   Updated: 2019/03/19 18:21:18 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <SDL2/SDL.h>

# include "../libft/libft.h"
# include "map.h"
# include "raycasting.h"

# define WIN_W 1600
# define WIN_H 1200
# define FPS_LIMIT 16
# define CAM_H 6
# define DUCK_CAM_H 2.5
# define STEP_H 2
# define COLLISION_HEAD 1
# define PI_X_2 M_PI * 2

# define M_GAME 42
# define M_EDITOR 69

typedef struct	s_raycasting
{
	int			i;
	t_window	wait[MAX_WAIT];
	t_window	*head;
	t_window	*tail;
	t_window	now;
	int			y_top[WIN_W];
	int			y_bot[WIN_W];
	t_sector	*sect;
	t_xy		v1;
	t_xy		v2;
	t_xy		t1;
	t_xy		t2;
	double		p_cos;
	double		p_sin;
	t_xy		near;
	t_xy		far;
	t_xy		i1;
	t_xy		i2;
	t_xy		scale1;
	t_xy		scale2;
	t_i_xy		lim_x;
	int			neighbor;
	double		y_floor;
	double		y_ceil;
	double		ny_floor;
	double		ny_ceil;
	t_i_xy		y;
	t_i_xy		y1;
	t_i_xy		y2;
	t_i_xy		c_y;
	t_i_xy		n_y;
	t_i_xy		c_n_y;
	t_i_xy		n_y1;
	t_i_xy		n_y2;
	t_i_xy		x_start_end;
	int			x;
	int			z;
	int			color_ceil;
	int			color_floor;
	int			color_wall;
}				t_raycasting;

typedef struct	s_moving
{
	int			s;
	t_xy		p;
	t_xy		d;
	t_xy		p_d;
	t_sector	*sect;
	t_xy		*vert;
	double		hole_low;
	double		hole_high;
	double		xd;
	double		yd;
}				t_moving;

typedef struct	s_move
{
	int			wsad[4];
	int			ground;
	int			falling;
	int			moving;
	int			ducking;
	double		yaw;
	double		eye_h;
	double		speed;
	double		gravity;
	int			duck_up;
}				t_move;

typedef struct	s_doom
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
	SDL_bool		bool_prog;
	SDL_Event		event;
	t_sector		*sectors;
	int				num_sectors;
	SDL_Surface		*surface;
	t_player		player;
	t_move			move;
	int				game_mode;
}				t_doom;

void			ft_init_doom(t_doom *doom);
void			ft_quit(t_doom *doom, const char *message, int error);
void			ft_read_map(int fd, t_doom *doom);
void			ft_read_sectors(t_doom *doom, t_read *r);
void			ft_tab_sectors(t_doom *doom, t_read *r);
void			ft_print_screen(t_doom *doom);
int				ft_intersect_box(t_xy p1, t_xy p2, t_xy p3, t_xy p4);
double			ft_point_side(t_xy p, t_xy p1, t_xy p2);
void			ft_event(t_doom *doom);
void			ft_move_player(t_doom *doom, double dx, double dy);
void			ft_move_wsad(t_doom *doom, t_move *move, t_player *player);
void			ft_move_mouse(t_doom *doom);
void			ft_moving(t_doom *doom, t_player *player);
void			ft_falling(t_doom *doom);
void			ft_check_duck_up(t_doom *doom);

void			render_game(t_doom *doom);

void			ft_limit_fps(unsigned int limit);

#endif
