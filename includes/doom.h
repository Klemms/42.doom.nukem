/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:12:03 by lde-batz          #+#    #+#             */
/*   Updated: 2019/04/19 05:12:00 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <SDL2/SDL.h>
# include <SDL2_ttf/SDL_ttf.h>
# include "../libft/libft.h"
# include "map.h"
# include "raycasting.h"
# include "errors.h"

# define CAM_H 6
# define DUCK_CAM_H 2.5
# define STEP_H 2
# define COLLISION_HEAD 1
# define PI_X_2 M_PI * 2

# define FONT_RIFFIC "fonts/Riffic.ttf"
# define FONT_SYS "fonts/fixedsys.ttf"

# define M_GAME 42
# define M_EDITOR 69

typedef struct	s_raycasting
{
	int			i;
	t_window	wait[MAX_WAIT];
	t_window	*head;
	t_window	*tail;
	t_window	now;
	int			*y_top;
	int			*y_bot;
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

typedef struct	s_settings
{
	int			window_width;
	int			window_height;
	float		framerate;
	float		angle_h;
	float		angle_v;
}				t_settings;

typedef struct	s_font
{
	TTF_Font	*font;
	int			size;
	char		*font_path;
}				t_font;

typedef struct	s_ui_element
{
	int			id;
	int			el_state;
	int			pos_x;
	int			pos_y;
	int			width;
	int			height;
}				t_el_ui;

typedef struct	s_text_element
{
	t_el_ui		*ui_element;
	SDL_Texture	*texture;
	SDL_Rect	rect;
	TTF_Font	*font;
	SDL_Color	text_color;
	int			list_id;
	char		*text;
	int			u_w;
	int			u_h;
}				t_el_text;

typedef struct s_doom t_doom;

typedef struct	s_button_element
{
	t_el_ui		*ui_element;
	void		(*ui_callback)(t_doom *doom, struct s_button_element *b, SDL_MouseButtonEvent event);
	SDL_Color	background_color;
	SDL_Color	background_color_disabled;
	t_el_text	*text;
	SDL_Rect	rect;
	int			is_disabled;
	int			is_visible;
}				t_el_button;

typedef struct	s_editor
{
	t_el_button	*test_button;
}				t_editor;

typedef struct	s_doom
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
	SDL_Event		event;
	t_sector		*sectors;
	int				num_sectors;
	SDL_Surface		*surface;
	t_player		player;
	t_move			move;
	t_lstcontainer	*events;
	Uint32			last_frame;
	t_settings		*settings;
	int				game_mode;
	t_lstcontainer	*fonts;
	t_lstcontainer	*texts;
	int				ui_ids;
	t_el_text		*fps_counter;
	t_el_text		*easter_egg;
	int				average_fps;
	t_editor		*editor;
	t_lstcontainer	*buttons;
}				t_doom;

typedef struct			s_registered_event
{
	Uint32				type;
	int					(*handler)(t_doom *doom, SDL_Event ev);
}						t_registered_event;

t_doom			*ft_init_doom();
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

TTF_Font		*make_font(t_doom *doom, char *font_path, int size);
void			init_fonts(t_doom *doom);
void			destroy_fonts(t_doom *doom);

void			exit_program(t_doom *doom, int err_code);

void			render_game(t_doom *doom);

void			init_game(t_doom *doom);
void			loop_game(t_doom *doom);

void			init_editor(t_doom *doom);
void			loop_editor(t_doom *doom);

void			ft_limit_fps(unsigned int limit);

void			init_ids(t_doom *doom);
int				next_id(t_doom *doom);

t_el_ui			*create_ui_element(t_doom *doom);
SDL_Color		make_rgb(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void			set_rgb(SDL_Color *color, int r, int g, int b);

t_el_text		*create_text(t_doom *doom, char *string, char *font_path, int size);
void			text_prepare(t_doom *doom, t_el_text *text, int make_size);
void			text_render(t_doom *doom, t_el_text *text);
int				text_size(t_el_text *text);

t_el_button		*create_button(t_doom *doom, char *string, SDL_Rect ps,
					void (*ui_callback)(t_doom *doom, t_el_button *b, SDL_MouseButtonEvent event));
void			button_prepare(t_doom *doom, t_el_button *button);
void			button_render(t_doom *doom, t_el_button *button);
int				button_coords_contained(t_el_button *button, int x, int y);
int				button_click(t_doom *doom, SDL_Event sdl_event);

SDL_Rect		make_rect(int x, int y, int width, int height);
void			draw_rect(t_doom *doom, SDL_Rect rect, SDL_Color color);

void			v2_init_events(t_doom *doom);
void			v2_register_event(t_doom *doom, Uint32 type,
					int (handler)(t_doom *doom, SDL_Event ev));
void			v2_distribute_events(t_doom *doom, SDL_Event sdl_event);

/** Eater Eggs **/
void			setup_hypercam(t_doom *doom);
void			render_hypercam(t_doom *doom);

#endif
