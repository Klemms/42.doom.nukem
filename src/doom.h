/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 13:43:48 by cababou           #+#    #+#             */
/*   Updated: 2019/04/30 16:17:04 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "mlx.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <time.h>

#include <stdio.h>

# include <Tk/X11/X.h>
# include "../libft/libft.h"
# include "errors/errors.h"

# define MODE_GAME 1
# define MODE_EDITOR 2

typedef struct		s_image
{
	void		*ptr;
	char		*img;
	int			bpp;
	int			s_l;
	int			endian;
	int			height;
	int			width;
}					t_image;

typedef struct		s_vec
{
	double	x;
	double	y;
	double	z;
}					t_vec;

typedef struct		s_line
{
	t_vec	cur;
	t_vec	dir;
	t_vec	inc;
	int		color;
}					t_line;

typedef struct		s_player
{
	t_vec		pos;
	t_vec		velocity;
	t_vec		dir;
	t_vec		plane;
	double		angle;
	double		anglecos;
	double		anglesin;
	double		pitch;
	double		speed;
	double		rotspeed;
	int			rov;
}					t_player;

typedef struct		s_map
{
	int		width;
	int		height;
	int		start_x;
	int		start_y;
	char	**m;
}					t_map;

typedef struct		s_key
{
	int		left;
	int		right;
	int		w;
	int		s;
	int		a;
	int		d;
	int		shadow;
}					t_key;

typedef struct		s_sight
{
	double	camera_x;
	t_vec	ray_dir;
	t_vec	pos;
	t_vec	side_dist;
	t_vec	delta_dist;
	double	perp_wall_dist;
	t_vec	step;
	int		hit;
	int		cpt;
	int		rov;
	int		side;
	int		tex;
}					t_sight;

typedef struct		s_doom
{
	void			*mlx;
	void			*window;
	int				w_width;
	int				w_height;
	t_image			img;
	t_map			map;
	t_player		you;
	t_key			keys;
	clock_t			oldtime;
	clock_t			curtime;
	double			fps;
	t_image			texture[4];
	int				temp_color;
	t_lstcontainer	*textures;
	t_sight			sight;
}					t_doom;

void				init_doom(t_doom *doom);
void				init_window(t_doom *doom);
void				init_mlx(t_doom *doom);
void				new_screen_image(t_doom *doom, t_image *img, int w, int h);
int					is_valid(t_doom *doom, int fd);

int					init_texture(t_doom *doom);

void				calc_perp_dist(t_sight *p, t_player *you);
int					see_wall(t_sight *p, t_doom *doom);
void				draw_wall(t_doom *doom, double x, int column, int tex);

void				new_player(t_doom *doom, t_map *map);
void				draw(t_doom *doom);
int					parsing(t_doom *doom, char *file);
int					key_down(int key, t_doom *doom);
int					key_up(int key, t_doom *doom);
void				line(t_doom *doom, t_vec *start, t_vec *end, int color);
int					loop(t_doom *doom);
void				calc_lov(t_doom *doom);
void				init_sight(t_doom *doom, t_sight *p, double x, t_player *you);
void				pixel_put(t_doom *doom, char *ptr, int x, int y);

void				exit_program(t_doom *doom, int code);
void				quit(t_doom *doom, char *message, int code);
int					close_window(t_doom *doom);
void				megafree_1(t_doom *doom);
#endif
