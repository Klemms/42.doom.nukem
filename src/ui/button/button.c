/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 02:04:31 by cababou           #+#    #+#             */
/*   Updated: 2019/05/01 05:18:18 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_el_button	*create_button(t_doom *doom, char *string, SDL_Rect rect,
	void (*ui_callback)(t_doom *doom, t_el_button *b, SDL_MouseButtonEvent event))
{
	t_el_button	*but;

	if (!(but = mmalloc(sizeof(t_el_button))))
		exit_program(doom, ERROR_SDL_AFTER_INIT);
	but->ui_element = create_ui_element(doom);
	but->text = create_text(doom, string, FONT_RIFFIC, 20);
	set_rgb(&but->background_color, 57, 114, 206);
	set_rgb(&but->background_color_disabled, 96, 136, 201);
	but->text->text_color = make_rgb(0, 0, 0, 255);
	but->ui_callback = ui_callback;
	but->is_visible = 1;
	but->rect = rect;
	lstcontainer_add(doom->buttons, but);
	return (but);
}

void		button_prepare(t_doom *doom, t_el_button *button)
{
	button->text->ui_element->pos_x
		= button->rect.x + button->rect.w / 2 - button->text->u_w / 2;
	button->text->ui_element->pos_y
		= button->rect.y + button->rect.h / 2 - button->text->u_h / 2;
	text_prepare(doom, button->text, 1);
}

void		button_render(t_doom *doom, SDL_Surface *surface, t_el_button *button)
{
	if (button->is_visible)
	{
		draw_rect(surface, button->rect, button->is_disabled ?
			button->background_color_disabled : button->background_color, 1);
		text_render(doom, surface, button->text);
	}
}
