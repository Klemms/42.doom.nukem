/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hypercam.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 03:54:08 by cababou           #+#    #+#             */
/*   Updated: 2019/05/01 00:32:58 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	setup_hypercam(t_doom *doom)
{
	doom->easter_egg = create_text(doom, "Unregistered HyperCam 2", FONT_SYS, 18);
	doom->easter_egg->ui_element->pos_x = doom->settings.window_width
		- doom->easter_egg->u_w - 4;
	doom->easter_egg->ui_element->pos_y = 3;
	set_rgb(&doom->easter_egg->text_color, 0, 0, 0);
	text_prepare(doom, doom->easter_egg, 1);
}

void	render_hypercam(t_doom *doom)
{
	draw_rect(doom, 
		make_rect(doom->settings.window_width - doom->easter_egg->u_w - 8,
			0, doom->easter_egg->u_w + 8, doom->easter_egg->u_h + 5),
		make_rgb(255, 255, 255, 255), 1);
	text_render(doom, doom->easter_egg);
}