/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 13:43:48 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 23:46:54 by lde-batz         ###   ########.fr       */
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
# include <SDL2_mixer/SDL_mixer.h>

# include "errors.h"

# define FONT_RIFFIC "fonts/Riffic.ttf"
# define FONT_SYS "fonts/fixedsys.ttf"

# define M_GAME 42
# define M_EDITOR 69

# define WIN_W 1920
# define WIN_H 1080

# define N_3_PI_4 -M_PI + M_PI_4
# define N_PI_4 -M_PI_4
# define P_3_PI_4 M_PI - M_PI_4

# define COL 0.1

/* Vector-like structs */
typedef struct 		s_xy
{
	float	x;
	float	y;
}					t_xy;

typedef struct		s_vec
{
	float	x;
	float	y;
	float	z;
}					t_vec;

typedef struct		s_vec_int
{
	int	x;
	int	y;
	int	z;
}					t_vec_int;
/*---------------------------*/

enum			e_map_valid
{
	map_good = 0,
	map_wall_contour = 1,
	map_spawn_point = 2,
	map_end_point = 3
};

enum			e_block_types
{
	block_air = 0,
	block_wall = 1,
	block_door = 2,
	block_spawn = 3,
	block_end = 4,
	block_copy = 5,
	block_window = 6,
	block_button = 7
};

enum			e_sprite_type
{
	sprite_key = 0,
	sprite_ammo = 1,
	sprite_health = 2,
	sprite_bullet = 3,
	sprite_dummy = 4,
	sprite_damage = 5
};

enum			e_render_modes
{
	rend_flat = 0,
	rend_door = 1,
	rend_window = 2
};

typedef struct	s_map_block
{
	int			block_type;
	int			orientation;
	int			x_size;
	int			y_size;
	int			event_id;
	int			ceiling_height;
	int			has_ceiling;
	int			ceilng_tex;
	int			floor_tex;
	int			n_texture;
	int			s_texture;
	int			w_texture;
	int			e_texture;
	int			light;
	int			collides;
	int			x;
	int			y;
	int			state;
}				t_mblock;

typedef struct	s_nmap
{
	char			*map_name;
	t_mblock		**map;
	int				size_x;
	int				size_y;
	SDL_Color		skybox_color;
	t_lstcontainer	*textures;
	t_lstcontainer	*sprites;
	int				spritecount;
}				t_nmap;

typedef struct	s_draw_wall
{
	double	line_height;
	int		start;
	int		end;
	int		py;
	int		wall_size;
}				t_draw_wall;

typedef struct	s_settings
{
	float		framerate;
	int			azerty_mode;
	int			default_wall_color;
	float		mouse_sensitivity;
	int			key_forward;
	int			key_backward;
	int			key_left;
	int			key_right;
	int			key_sprint;
	int			key_crouch;
	int			key_button;
	int			render_textures;
	int			enable_crt_floor;
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
	t_el_ui		*ui;
	SDL_Surface	*surface;
	SDL_Rect	rect;
	TTF_Font	*font;
	SDL_Color	text_color;
	int			list_id;
	char		*text;
	int			u_w;
	int			u_h;
}				t_el_text;

typedef struct	s_whjauge_element
{
	t_el_ui		*ui;
	t_el_text	*txt;
	SDL_Rect	pos;
	SDL_Color	background;
	SDL_Color	border;
	SDL_Color	color;
	int			min;
	int			max;
	int			value;
	int			step;
	int			is_focused;
	char		*unit;
}				t_el_wh_jauge;

typedef struct	s_checkbox_element
{
	t_el_ui		*ui;
	SDL_Rect	pos;
	SDL_Color	disabled_c;
	SDL_Color	background;
	SDL_Color	border;
	SDL_Color	color;
	int			checked;
	int			disabled;
}				t_el_checkbox;

typedef struct s_doom t_doom;

typedef struct	s_button_element
{
	t_el_ui		*ui;
	void		(*ui_callback)(t_doom *doom, struct s_button_element *b, SDL_MouseButtonEvent event);
	SDL_Color	background_color;
	SDL_Color	background_color_disabled;
	t_el_text	*text;
	SDL_Rect	rect;
	int			is_disabled;
	int			is_visible;
	int			real_x;
	int			real_y;
}				t_el_button;

typedef struct	s_block_type
{
	char		*block_name;
	Uint32		block_color;
	int			block_type;
}				t_block_type;

typedef struct	s_sprite_type
{
	char		*sprite_name;
	Uint32		sprite_color;
	int			sprite_type;
}				t_sprite_type;

typedef struct	s_quadrant_renderer
{
	int				zoom_level;
	int				x_start;
	int				y_start;
	int				pos_x;
	int				pos_y;
	t_el_button		*orient_hor;
	t_el_button		*orient_ver;
	t_el_button		*texture_n;
	t_el_button		*texture_s;
	t_el_button		*texture_w;
	t_el_button		*texture_e;
	t_el_wh_jauge	*ev_id;
	t_el_wh_jauge	*sc_height;
	t_el_wh_jauge	*b_w;
	t_el_wh_jauge	*b_h;
	t_el_checkbox	*has_celng;
	t_el_checkbox	*sp_collides;
	t_el_checkbox	*sp_obtainable;
}				t_quadrant_renderer;

typedef struct	s_ed_focus
{
	int			b_block_type;
	int			b_orientation;
	int			b_x_size;
	int			b_y_size;
	int			b_event_id;
	int			b_ceiling_height;
	int			b_has_ceiling;
	int			b_ceilng_tex;
	int			b_floor_tex;
	int			b_n_texture;
	int			b_s_texture;
	int			b_w_texture;
	int			b_e_texture;
	int			b_light;
	int			b_collides;
}				t_ed_focus;

typedef struct	s_ed_focuss
{
	int		b_texture;
	int		b_texture_back;
	int		b_collides;
	int		b_obtainable;
	int		b_type;
}				t_ed_focuss;

typedef struct	s_editor
{
	SDL_Surface			*ed_surface;
	int					in_x;
	int					in_y;
	int					in_width;
	int					in_height;
	int					sep_size;
	int					square_width;
	int					square_height;
	SDL_Surface			*ftr;
	SDL_Rect			ftr_rect;
	t_quadrant_renderer	ftr_quadrant;
	SDL_Surface			*bsr;
	SDL_Rect			bsr_rect;
	t_quadrant_renderer	bsr_quadrant;
	SDL_Surface			*rbr;
	SDL_Rect			rbr_rect;
	t_quadrant_renderer	rbr_quadrant;
	int					wheel_pressed;
	int					anim_finished;
	int					anim_w;
	int					anim_h;
	Uint8				anim_alpha;
	t_el_button			*tool_block;
	t_el_button			*tool_none;
	t_el_button			*tool_sprite;
	int					hand_tool;
	t_block_type		*selected_block;
	t_sprite_type		*selected_sprite;
	t_el_text			*current_tool;
	t_el_text			*str_tool;
	int					c_focus;
	int					x_focus;
	int					y_focus;
	t_ed_focus			foc;
	t_ed_focuss			foc_s;
	SDL_Color			base_color;
	SDL_Color			select_color;
	t_el_button			*validate;
	t_el_button			*save;
	t_el_text			*state;
	int					is_clicking;
	t_lstcontainer		*l_textures;
	int					texture_edited;
}				t_editor;

typedef struct		s_sprite
{
	t_vec	vel;
	t_vec	pos;
	int		texture;
	int		texture_back;
	int		render_mode;
	int		base_x;
	int		base_y;
	int		collides;
	int		obtainable;
	double	stage;
	int     animated;
	int		type;
	int		dontsave;
	int		texture_id;
}					t_sprite;

typedef struct		s_line
{
	t_vec	cur;
	t_vec	dir;
	t_vec	inc;
	int		color;
}					t_line;

typedef struct		s_hud
{
	int				health;
	int				ammo;
	int				key;
	SDL_Surface		*gun_1;
	SDL_Surface		*gun_3;
	SDL_Surface		*key_h;
	SDL_Surface		*ammo_tt;
}					t_hud;

typedef struct		s_player
{
	t_vec			pos;
	t_vec			velocity;
	t_vec			dir;
	t_vec			plane;
	float			angle;
	double			anglecos;
	double			anglesin;
	float			pitch;
	float			speed;
	int				rov;
	int				is_sprinting;
	int				is_crouching;
	int				moving;
	t_hud			hud;
	int				is_walking;
}					t_player;

typedef struct		s_key
{
	int		left;
	int		right;
	int		up;
	int		down;
	int		z_up;
	int		z_down;
	int		shadow;
}					t_key;

typedef struct		s_musics
{
	Mix_Music	*bgm;
	Mix_Chunk	*walk;
	Mix_Chunk	*shot;
	Mix_Chunk	*damage;
}					t_musics;


typedef struct		s_texture
{
	SDL_Surface	*surface;
	char		*texture_name;
	int			tex_pixels;
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

typedef struct 	s_l_sprite
{
	int		  numbSprites;
	int       *spritesOrder;
	double    *spritesDist;
}				t_l_sprite;

typedef struct		s_raycasting
{
	SDL_Surface	*texture;
	int			x;
	double		p_z;
	double		camera_x;
	t_vec		ray_dir;
	t_vec_int	map;
	t_vec		side_dist;
	t_vec		delta_dist;
	t_vec_int   step;
	int			side;
	int			dist_hit; // nb of boxes crossed by ray before hitting
	double		perp_wall_dist;
	int			lineHeight;
	int			draw_start;
	int			draw_end;
	t_vec_int	tex;
	t_vec		floor;
	t_vec_int	floor_tex;
	double		wall_x;
	// SPRITES
	int			v_move_screen;
	t_vec		rel_sprite_pos;
	t_vec		transform;
	int			sprite_screen_x;
	int 		sprite_height;
	int 		sprite_width;
	int			draw_start_x;
	int			draw_end_x;
	int			draw_start_y;
	int			draw_end_y;
	int			tex_x;
	int			tex_y;
	t_sprite	*cur_sprite;
}					t_raycasting;

typedef struct		s_doom
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
	SDL_Event		last_event;
	SDL_Surface		*surface;
	Uint32			*s_pixels;
	t_lstcontainer	*events;
	Uint32			last_frame;
	t_settings		settings;
	int				original_mode;
	int				game_mode;
	t_lstcontainer	*fonts;
	t_lstcontainer	*texts;
	int				ui_ids;
	t_el_text		*fps_counter;
	t_el_text		*easter_egg;
	int				average_fps;
	t_editor		editor;
	t_lstcontainer	*buttons;
	t_player		you;
	t_key			keys;
	int				temp_color;
	SDL_Color		tmp_color;
	int				texture_amount;
	t_raycasting	raycasting;
	int				mouse_focused;
	int				game_init;
	t_nmap			*nmap;
	int				m_x; // Mouse X // Both Updated each frame
	int				m_y; // Mouse Y
	t_musics			musics;
	t_lstcontainer	*block_types;
	t_l_sprite		lsprite;
	t_lstcontainer	*sprite_types;
}					t_doom;

typedef struct		s_rtxt
{
	int				j;
	int				max;
	t_texture		*txt;
	SDL_Surface		*s;
	int				w;
	int				h;
	int				k;
}					t_rtxt;

typedef struct		s_rtx
{
	int				sz;
	void			*data;
}					t_rtx;

typedef struct		s_registered_event
{
	Uint32			type;
	int				gamemode;
	int				(*handler)(t_doom *doom, SDL_Event ev);
}					t_registered_event;

typedef struct		s_validate
{
	int				x;
	int				y;
	int				spawn_points;
	int				end_points;
}					t_validate;

void				init_block_types(t_doom *doom);
void				init_sprite_types(t_doom *doom);
void				init_window(t_doom *w);
void				init_sdl(t_doom *w);
int					is_valid(t_doom *w, int fd);

void				init_textures(t_doom *doom);
t_texture			*make_texture(t_doom *doom, SDL_Surface *surface, char *texture_name);
t_texture			*load_texture(t_doom *doom, char *path);
SDL_Surface			*get_surface(t_doom *doom, int texture_id);

//void				draw_wall(t_doom *w, double x, double column, int tex);
//void				draw_floor(t_doom *doom, double x, int column);

void    			draw_screen(t_doom *doom);
void 				draw_wfc(t_doom *doom, double **z_buffer);
void  				wfc_init(t_raycasting *rc, t_player *p);
void  				wfc_rayhit(t_raycasting *rc, t_player *p, t_nmap *nmap);
void  				wfc_wall_init(t_raycasting *rc, t_player *p);
void  				wfc_wall_draw(t_raycasting *rc, Uint32 **canvas);
void  				wfc_fc_init(t_raycasting *rc);
void  				wfc_floor_draw(t_raycasting *rc, t_player *p, Uint32 **canvas);
void  				wfc_ceiling_draw(t_raycasting *rc, t_player *p, Uint32 **canvas);
void    			draw_sprites(t_doom *doom, t_raycasting *rc, t_player *p, double **z_buffer, Uint32 **canvas, t_l_sprite *lsprite); //soz
void    			sprite_flat_init(t_raycasting *rc, t_player *p, int i, t_sprite *sprite, int *spriteOrder);
void              	sprite_flat_draw(t_raycasting *rc, double **z_buffer, Uint32 **canvas);
void    			sprite_door_init(t_raycasting *rc, t_player *p);

Uint32            	calc_gradient(Uint32 color1, Uint32 color2, double stage);
void  				swap(double *a, double *b);
void 				combSort(int* order, double* dist, int amount);

void				new_player(t_doom *doom, t_player *player, t_nmap *nmap);
int					draw(t_doom *w);
int					parsing(t_doom *w, char *file);
int					key_down(t_doom *doom, SDL_Event event);
int					key_up(t_doom *doom, SDL_Event event);
int					mouse_down(t_doom *doom, SDL_Event event);
void				line(t_doom *w, t_vec *start, t_vec *end, int color);
int					loop(t_doom *w);
Uint32				get_t_exact_pixel(t_texture *texture, int x, int y);

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
void				render_hypercam(t_doom *doom, SDL_Surface *surface);

void				init_game(t_doom *doom);
void				loop_game(t_doom *doom);
void				game_loop(t_doom *doom, t_settings *sett);
void				render_game(t_doom *doom);
void				update_velocity(t_doom *doom, t_player *player);
void				moving(t_doom *doom);
void				moving2(t_doom *d);
t_xy				pt_angle(t_doom *doom);
void				moving_diagonal(t_doom *doom, t_xy *dest, t_xy pt);
int					check_sprite(t_doom *doom, t_list *sprites, t_sprite *sprite, t_xy *dest);
void				moving_sprite(t_doom *doom);

void				press_button(t_doom *doom);

void				init_musics(t_doom *doom);

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

void				instant_text(t_doom *d, SDL_Surface *s, char *st, SDL_Rect poscols);
t_el_text			*create_text(t_doom *doom, char *string, char *font_path, int size);
void				text_prepare(t_doom *doom, t_el_text *text, int mk_size, int cent);
void				text_render(t_doom *doom, SDL_Surface *surface, t_el_text *text);
int					text_size(t_el_text *text);

t_el_button			*create_button(t_doom *doom, char *string, SDL_Rect ps,
						void (*ui_callback)(t_doom *doom, t_el_button *b, SDL_MouseButtonEvent event));
void				button_prepare(t_doom *doom, t_el_button *button);
void				button_render(t_doom *doom, SDL_Surface *surface, t_el_button *button);
void				button_render_texture(t_doom *d, SDL_Surface *s, t_el_button *b, SDL_Surface *b_text);
int					button_coords_contained(t_el_button *button, int x, int y);
void				add_button_rcoords(t_el_button *but, int x, int y);
int					button_click(t_doom *doom, SDL_Event sdl_event);

t_el_wh_jauge		*create_wjauge(t_doom *d, SDL_Rect rc, SDL_Rect mmvs);
void				wjauge_render(t_doom *d, SDL_Surface *s, t_el_wh_jauge *jg);
void				wjauge_prepare(t_doom *d, t_el_wh_jauge *jg);
void				wjauge_set(t_doom *d, t_el_wh_jauge *jg, int value, int prepare);
void				wjauge_affect(t_doom *d, t_el_wh_jauge *jg, int change, int prepare);

t_el_checkbox		*create_checkbox(t_doom *d, SDL_Rect pos, int checked);
void				checkbox_render(t_doom *d, SDL_Surface *s, t_el_checkbox *ck);

SDL_Rect			make_rect(int x, int y, int width, int height);
void				draw_rect(SDL_Surface *s, SDL_Rect rect, SDL_Color color, int fill_rect);
void				draw_rect_u(SDL_Surface *s, SDL_Rect rect, Uint32 color, int fill_rect);

void				turn(double angle, t_player *player);

void				ed_bt_edit_click(t_doom *doom, t_el_button *b, SDL_MouseButtonEvent ev);

void				editor_init_map(t_doom *doom);

void				editor_ftr_brender(t_doom *doom);
void				editor_ftr_mrender(t_doom *doom);
void				editor_ftr_clicked(t_doom *doom);
void				editor_rbr_brender(t_doom *doom);
void				editor_rbr_mrender(t_doom *doom);
int					rbr_wheel(t_doom *d, SDL_Event event);
int					rbr_click(t_doom *d, SDL_Event event);

void				editor_rbrs_mrender(t_doom *d);
int					rbrs_click(t_doom *d, SDL_Event event);
void				ed_sprite_list(t_doom *d);

void				editor_bsr_brender(t_doom *doom);
void				editor_bsr_mrender(t_doom *doom);
t_sprite_type		*get_sprite_type(t_doom *d, int type);

void				switch_to_game(t_doom *doom);
void				switch_to_editor(t_doom *doom);
void				fade_surface(t_doom *doom);
void				fade_surface_back(t_doom *doom);

Uint32				color_to_uint(SDL_Color color);
int					mouse_in(int m_x, int m_y, SDL_Rect rect);
SDL_Rect			mouse_pos();
int					is_left_clicking();
int					is_right_clicking();

void				switch_tool(t_doom *doom, int to_tool, t_block_type *block);
void				switch_tool_sprite(t_doom *doom, int to_tool, t_sprite_type *sp);

t_block_type		*make_block_type(t_doom *doom, char *bn, Uint32 bc, int bt);
t_block_type		*block_type(t_doom *d, int bt);
t_sprite_type		*make_sprite_type(t_doom *doom, char *bn, Uint32 bc, int bt);

void				select_block_type(t_doom *d, t_block_type *type);
void				copy_block_type(t_doom *d, t_block_type *type, t_mblock *blk);
void				copy_block(t_mblock *dest, t_mblock *src, int free2, int cpcrds);
void				update_interactions(t_doom *d);
void				update_interactions_sprite(t_doom *d);
void				select_sprite_type(t_doom *d, t_sprite_type *type);
void				set_to_default_mblock(t_mblock *dest, int x, int y);
void				apply_block_settings(t_doom *d, t_mblock *dest);
void				apply_block_texture(t_doom *d, int texture_id);

int					validate_map(t_doom *d, t_nmap *m);
void				ed_save_file(t_doom *d, t_el_button *b, SDL_MouseButtonEvent ev);
void				ed_test_map(t_doom *d, t_el_button *b, SDL_MouseButtonEvent ev);
char				*map_reason_to_txt(int reason);
int					player_valid_tile(t_player *pl, t_nmap *nmap);
t_mblock			*get_spawn_point(t_nmap *nmap);
int					write_map(t_nmap *m, char *path);
int					read_map(t_doom *d, char *path);
void				write_intdl(int fd, int i, int comma, int endl);
void				wrt_textures(t_nmap *m, int fd);
void				wrt_sprites(t_nmap *m, int fd);
void				read_blockline(t_doom *d, t_nmap *m, int y, char *l);
t_nmap				*load_map(t_doom *d, char *path);
void				read_texture(t_doom *d, t_nmap *m, char *l);
void				lm_1(t_doom *d, int *state, t_nmap *m, char *line);
void				lm_2(int *y, int *state, t_nmap *m, char *line);
void				lm_3(int *y, int *state, t_nmap *m, char *line);
void				read_sprites(t_doom *d, t_nmap *m, char *l);
int					spritecount(t_list *sprites);

void				teleport_player(t_player *player, double x, double y, double z);

unsigned int		checksum(void *data, size_t size, unsigned int seed);

void				draw_minimap(t_doom *d);

t_lstcontainer		*list_files(char *folder_path);

void				expand_map(t_doom *d, t_nmap *m, t_mblock *b);
t_mblock			*new_block(t_doom *d, int block_type, int x, int y);
int					add_texture(t_doom *d, char *texture_name);

int					mgnc(char *str, char c);

void				render_sprites(t_doom *d);
void				add_sprite(t_doom *d, int x, int y);
void				remove_sprite(t_doom *d, t_list *s);

void				blockwindowdoor_added(t_doom *d, t_mblock *b);
void				blockwindowdoor_removed(t_doom *d, int type, int x, int y);

void				init_hud(t_doom *d);
void				render_hud(t_doom *d);

t_sprite			*make_doorwindowsprite(t_doom *d, t_mblock *b);

#endif
