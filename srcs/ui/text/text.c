/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 03:48:04 by cababou           #+#    #+#             */
/*   Updated: 2019/04/18 06:30:13 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_el_text	*create_text(t_doom *doom, t_el_ui *ui, char *string)
{
	t_el_text	*text;

	if (!(text = mmalloc(sizeof(t_el_text))))
		exit_program(doom, QUIT_MEMERR_AFTER_SDLINIT);
	lstcontainer_add(doom->texts, text);
	text->list_id = doom->texts->lastelement->index;
	text->ui_element = ui;
	text->text_color.r = 255;
	text->text_color.g = 255;
	text->text_color.b = 255;
	text->text_color.a = 255;
	text->font = doom->fonts->firstelement->content;
	text->text = string;
	return (text);
}

void		text_prepare(t_doom *doom, t_el_text *text)
{
	SDL_Surface *surface;
	
	surface = TTF_RenderText_Solid(
		text->font,
		text->text,
		text->text_color);
	text->texture = SDL_CreateTextureFromSurface(doom->rend, surface);
	SDL_FreeSurface(surface);
	text->rect.x = text->ui_element->pos_x;
	text->rect.y = text->ui_element->pos_y;
	text->rect.w = text->ui_element->width;
	text->rect.h = text->ui_element->height;
}

void		text_render(t_doom *doom, t_el_text *text)
{
	SDL_RenderCopy(doom->rend, text->texture, NULL, &text->rect);
}
