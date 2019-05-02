/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 03:48:04 by cababou           #+#    #+#             */
/*   Updated: 2019/05/02 05:07:42 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		instant_text(t_doom *d, SDL_Surface *s, char *st, SDL_Rect poscols)
{
	SDL_Surface *su;
	TTF_Font	*f;
	int			w;
	int			h;
	SDL_Rect	rect;

	f = make_font(d, FONT_RIFFIC, poscols.w);
	su = TTF_RenderUTF8_Blended(
		f,
		st,
		d->tmp_color);
	TTF_SizeUTF8(f, st, &w, &h);
	rect = make_rect(poscols.x, poscols.y, w, h);
	SDL_BlitSurface(su, NULL, s, &rect);
	SDL_FreeSurface(su);
}

t_el_text	*create_text(t_doom *doom, char *string, char *font_path, int size)
{
	t_el_text	*text;

	if (!(text = mmalloc(sizeof(t_el_text))))
		exit_program(doom, ERROR_SDL_AFTER_INIT);
	lstcontainer_add(doom->texts, text);
	text->list_id = doom->texts->lastelement->index;
	text->ui_element = create_ui_element(doom);
	text->text_color.r = 255;
	text->text_color.g = 255;
	text->text_color.b = 255;
	text->text_color.a = 255;
	text->font = make_font(doom, font_path, size);
	text->text = ft_strdup(string);
	text_size(text);
	text->ui_element->width = text->u_w;
	text->ui_element->height = text->u_h;
	return (text);
}

void		text_prepare(t_doom *doom, t_el_text *text, int make_size)
{
	text->surface = TTF_RenderUTF8_Blended(
		text->font,
		text->text,
		text->text_color);
	/*text->texture = SDL_CreateTextureFromSurface(doom->rend, surface);
	SDL_FreeSurface(surface);*/
	if (make_size)
	{
		text_size(text);
		text->ui_element->width = text->u_w;
		text->ui_element->height = text->u_h;
	}
	text->rect.x = text->ui_element->pos_x;
	text->rect.y = text->ui_element->pos_y;
	text->rect.w = text->ui_element->width;
	text->rect.h = text->ui_element->height;
}

void		text_render(t_doom *doom, SDL_Surface *surface, t_el_text *text)
{
	SDL_BlitSurface(text->surface, NULL, surface, &text->rect);
	//SDL_RenderCopy(doom->rend, text->texture, NULL, &text->rect);
}
