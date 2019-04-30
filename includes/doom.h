/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 13:43:48 by cababou           #+#    #+#             */
/*   Updated: 2019/04/30 20:38:15 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <time.h>
# include <SDL2/SDL.h>
# include <SDL2_ttf/SDL_ttf.h>
# include <SDL2_image/SDL_image.h>

# include "errors.h"

# define FONT_RIFFIC "fonts/Riffic.ttf"
# define FONT_SYS "fonts/fixedsys.ttf"

# define M_GAME 42
# define M_EDITOR 69

typedef struct	s_settings
{
	int			window_width;
	int			window_height;
	float		framerate;
	float		angle_h;
	float		angle_v;
	int			azerty_mode;
	int			default_wall_color;
	float		mouse_sensitivity;
	int			key_forward;
	int			key_backward;
	int			key_left;
	int			key_right;
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
	int			in_x;
	int			in_y;
	int			in_width;
	int			in_height;
	int			sep_size;
	int			square_width;
	int			square_height;
}				t_editor;

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
	t_vec			pos;
	t_vec			velocity;
	t_vec			dir;
	t_vec			plane;
	double			angle;
	double			anglecos;
	double			anglesin;
	double			pitch;
	double			speed;
	double			rotspeed;
	int				rov;
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
	int		up;
	int		down;
	int		shadow;
}					t_key;

typedef struct		s_texture
{
	SDL_Surface	*surface;
	char		*texture_name;
}					t_texture;

typedef struct		s_wall_sight
{
	double				x;
	double				y;
	double				z;
	double				side;
	int					tex;
	int					next_x;
	int					next_y;
	double				next_perp;
}					t_wall_sight;

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
	t_wall_sight	saw_that[40]; // Must be sized[you->rov]
	int				queue_cpt;
}					t_sight;

typedef struct		s_doom
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
	SDL_Event		last_event;
	SDL_Surface		*surface;
	t_lstcontainer	*events;
	Uint32			last_frame;
	t_settings		settings;
	int				game_mode;
	t_lstcontainer	*fonts;
	t_lstcontainer	*texts;
	int				ui_ids;
	t_el_text		*fps_counter;
	t_el_text		*easter_egg;
	int				average_fps;
	t_editor		editor;
	t_lstcontainer	*buttons;
	t_map			map;
	t_player		you;
	t_key			keys;
	int				temp_color;
	t_lstcontainer	*textures;
	t_sight			sight;
}					t_doom;

typedef struct			s_registered_event
{
	Uint32				type;
	int					(*handler)(t_doom *doom, SDL_Event ev);
}						t_registered_event;

void				init_window(t_doom *w);
void				init_sdl(t_doom *w);
int					is_valid(t_doom *w, int fd);

void				init_textures(t_doom *doom);
t_texture			*make_texture(t_doom *doom, SDL_Surface *surface, char *texture_name);
SDL_Surface			*get_surface(t_doom *doom, int texture_id);

double				calc_perp_dist(t_sight *p, t_player *you, int num);
double				calc_perp_dist_next(t_sight *p, t_player *you, int num, int num2);
int					see_wall(t_sight *p, t_doom *w);
void				draw_wall(t_doom *w, double x, int column, int tex);

void				new_player(t_doom *doom, t_player *player, t_map *map);
int					draw(t_doom *w);
int					parsing(t_doom *w, char *file);
int					key_down(t_doom *doom, SDL_Event event);
int					key_up(t_doom *doom, SDL_Event event);
void				line(t_doom *w, t_vec *start, t_vec *end, int color);
int					loop(t_doom *w);
void				calc_lov(t_doom *w);
void				init_sight(t_doom *doom, t_sight *p, double x, t_player *you);
void				pixel_put(t_doom *w, int x, int y, int color);

int					mouse_movement(t_doom *doom, SDL_Event event);

void				exit_program(t_doom *w, int code);
void				quit(t_doom *w, char *message, int code);
int					quit_window(t_doom *doom, SDL_Event ev);
void				megafree_1(t_doom *w);

void				init_events(t_doom *doom);
void				register_event(t_doom *doom, Uint32 type,
						int (handler)(t_doom *doom, SDL_Event ev));
void				distribute_events(t_doom *doom, SDL_Event sdl_event);

void				setup_hypercam(t_doom *doom);
void				render_hypercam(t_doom *doom);

void				init_game(t_doom *doom);
void				loop_game(t_doom *doom);
void				render_game(t_doom *doom);

void				init_editor(t_doom *doom);
void				loop_editor(t_doom *doom);
void				render_editor(t_doom *doom);

void				init_ids(t_doom *doom);
int					next_id(t_doom *doom);

TTF_Font			*make_font(t_doom *doom, char *font_path, int size);
void				init_fonts(t_doom *doom);
void				destroy_fonts(t_doom *doom);

t_el_ui				*create_ui_element(t_doom *doom);
SDL_Color			make_rgb(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void				set_rgb(SDL_Color *color, int r, int g, int b);

t_el_text			*create_text(t_doom *doom, char *string, char *font_path, int size);
void				text_prepare(t_doom *doom, t_el_text *text, int make_size);
void				text_render(t_doom *doom, t_el_text *text);
int					text_size(t_el_text *text);

t_el_button			*create_button(t_doom *doom, char *string, SDL_Rect ps,
						void (*ui_callback)(t_doom *doom, t_el_button *b, SDL_MouseButtonEvent event));
void				button_prepare(t_doom *doom, t_el_button *button);
void				button_render(t_doom *doom, t_el_button *button);
int					button_coords_contained(t_el_button *button, int x, int y);
int					button_click(t_doom *doom, SDL_Event sdl_event);

SDL_Rect			make_rect(int x, int y, int width, int height);
void				draw_rect(t_doom *doom, SDL_Rect rect, SDL_Color color);

void				turn(double angle, t_player *you);
void				moove(double dist, t_player *you, t_map *map, int ang);

#endif
