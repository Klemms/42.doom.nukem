/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 03:48:04 by cababou           #+#    #+#             */
/*   Updated: 2019/04/30 16:16:38 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
	text->text = string;
	text_size(text);
	text->ui_element->width = text->u_w;
	text->ui_element->height = text->u_h;
	return (text);
}

void		text_prepare(t_doom *doom, t_el_text *text, int make_size)
{
	SDL_Surface *surface;
	
	surface = TTF_RenderUTF8_Blended(
		text->font,
		text->text,
		text->text_color);
	text->texture = SDL_CreateTextureFromSurface(doom->rend, surface);
	SDL_FreeSurface(surface);
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

void		text_render(t_doom *doom, t_el_text *text)
{
	SDL_RenderCopy(doom->rend, text->texture, NULL, &text->rect);
}
