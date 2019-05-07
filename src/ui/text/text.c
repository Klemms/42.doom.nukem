/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 03:48:04 by cababou           #+#    #+#             */
/*   Updated: 2019/05/08 00:11:34 by cababou          ###   ########.fr       */
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

	if ((f = make_font(d, FONT_RIFFIC, poscols.w)))
	{
		su = TTF_RenderUTF8_Blended(
			f,
			st,
			d->tmp_color);
		TTF_SizeUTF8(f, st, &w, &h);
		rect = make_rect(poscols.x, poscols.y, w, h);
		SDL_BlitSurface(su, NULL, s, &rect);
		SDL_FreeSurface(su);
	}
	if (poscols.h)
		free(st);
}

t_el_text	*create_text(t_doom *doom, char *string, char *font_path, int size)
{
	t_el_text	*text;

	if (!(text = mmalloc(sizeof(t_el_text))))
		exit_program(doom, ERROR_SDL_AFTER_INIT);
	lstcontainer_add(doom->texts, text);
	text->surface = NULL;
	text->list_id = doom->texts->lastelement->index;
	text->ui = create_ui_element(doom);
	text->text_color.r = 255;
	text->text_color.g = 255;
	text->text_color.b = 255;
	text->text_color.a = 255;
	if (!(text->font = make_font(doom, font_path, size)))
	{
		free(text->ui);
		free(text);
		return (NULL);
	}
	text->text = ft_strdup(string);
	text_size(text);
	text->ui->width = text->u_w;
	text->ui->height = text->u_h;
	return (text);
}

void		text_prepare(t_doom *doom, t_el_text *text, int mk_size, int cent)
{
	(void)doom;
	if (!text)
		return ;
	SDL_FreeSurface(text->surface);
	text->surface = TTF_RenderUTF8_Blended(
		text->font,
		text->text,
		text->text_color);
	if (mk_size)
	{
		text_size(text);
		text->ui->width = text->u_w;
		text->ui->height = text->u_w;
	}
	text->rect.x = cent ? text->ui->pos_x - text->u_w / 2 : text->ui->pos_x;
	text->rect.y = cent ? text->ui->pos_y - text->u_h / 2 : text->ui->pos_y;
	text->rect.w = text->ui->width;
	text->rect.h = text->ui->height;
}

void		text_render(t_doom *doom, SDL_Surface *surface, t_el_text *text)
{
	if (!text)
		return ;
	(void)doom;
	SDL_BlitSurface(text->surface, NULL, surface, &text->rect);
}
