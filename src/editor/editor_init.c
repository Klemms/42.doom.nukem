/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 22:57:58 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/07 23:30:43 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "editor.h"

void	register_event_init(t_doom *doom)
{
	register_event(doom, SDL_QUIT, quit_event);
	register_event(doom, SDL_KEYUP, key_event);
	register_event(doom, SDL_MOUSEBUTTONUP, button_click);
	register_event(doom, SDL_MOUSEWHEEL, zoom_event);
	register_event(doom, SDL_MOUSEWHEEL, rbr_wheel);
	register_event(doom, SDL_MOUSEBUTTONDOWN, ed_mouse_button);
	register_event(doom, SDL_MOUSEBUTTONUP, ed_mouse_button);
	register_event(doom, SDL_MOUSEBUTTONUP, rbr_click);
	register_event(doom, SDL_MOUSEBUTTONUP, rbrs_click);
	register_event(doom, SDL_MOUSEMOTION, ed_mouse_motion);
}

void	init_editor1(t_doom *doom, t_editor *e)
{
	e->selected_block = NULL;
	e->l_textures = list_files("./textures/");
	e->ftr_rect = make_rect(e->in_x, e->in_y, e->in_width, e->in_height);
	e->ftr = SDL_CreateRGBSurfaceWithFormat(0, e->in_width,
	e->in_height, 32, doom->surface->format->format);
	e->ftr_quadrant.zoom_level = e->ftr_rect.h / doom->nmap->size_y * 0.9;
	e->ftr_quadrant.x_start = e->ftr_rect.w / 2 - doom->nmap->size_x
	* e->ftr_quadrant.zoom_level / 2;
	e->ftr_quadrant.y_start = e->ftr_rect.h / 2 - doom->nmap->size_y
	* e->ftr_quadrant.zoom_level / 2;
	e->ftr_quadrant.pos_x = e->ftr_rect.x;
	e->ftr_quadrant.pos_y = e->ftr_rect.y;
	e->bsr_rect = make_rect(0, WIN_H - 300, WIN_W - 300, 300);
	e->bsr = SDL_CreateRGBSurfaceWithFormat(0, e->bsr_rect.w, e->bsr_rect.h, 32,
		doom->surface->format->format);
	e->bsr_quadrant.pos_x = e->bsr_rect.x;
	e->bsr_quadrant.pos_y = e->bsr_rect.y;
	e->rbr_rect = make_rect(WIN_W - 300, 80, 300, WIN_H - 80);
	e->rbr = SDL_CreateRGBSurfaceWithFormat(0, e->rbr_rect.w, e->rbr_rect.h, 32,
		doom->surface->format->format);
	e->rbr_quadrant.pos_x = e->rbr_rect.x;
	e->rbr_quadrant.pos_y = e->rbr_rect.y;
	e->tool_none = create_button(doom, "None",
		make_rect(10, 125, 60, 60), ed_none_c);
}

void	init_editor(t_doom *doom)
{
	t_editor	*e;

	e = &doom->editor;
	e->anim_finished = 1;
	e->ed_surface = SDL_CreateRGBSurfaceWithFormat(0, WIN_W, WIN_H, 32,
		doom->surface->format->format);
	init_editor_sizes(doom);
	e->base_color = make_rgb(145, 145, 145, 255);
	e->select_color = make_rgb(150, 150, 115, 255);
	e->c_focus = -1;
	e->x_focus = -1;
	e->y_focus = -1;
	register_event_init(doom);
	editor_init_map(doom);
	init_editor1(doom, e);
	init_editor2(doom, e);
	init_editor3(doom, e);
	init_editor4(doom, e);
	init_editor5(doom, e);
	init_editor6(doom, e);
}
