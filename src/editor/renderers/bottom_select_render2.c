/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bottom_select_render2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 10:51:30 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 21:36:02 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	render_sprite_apply(t_doom *d, t_list *tmp, int x, int y)
{
	t_sprite_type	*tmp_bt;

	tmp_bt = tmp->content;
	draw_rect_u(d->editor.bsr, make_rect(x, y, 170, 70),
		tmp_bt->sprite_color, 1);
	d->tmp_color = make_rgb(0, 0, 0, 255);
	instant_text(d, d->editor.bsr,
		tmp_bt->sprite_name, make_rect(x + 10, y + 22, 20, 0));
	if (is_left_clicking() && mouse_in(d->m_x, d->m_y,
			make_rect(d->editor.bsr_rect.x
				+ x, d->editor.bsr_rect.y + y, 170, 70)))
		select_sprite_type(d, tmp_bt);
}

void	render_sprites(t_doom *d)
{
	t_list			*tmp;
	int				x;
	int				y;

	d->tmp_color = make_rgb(255, 255, 255, 255);
	instant_text(d, d->editor.bsr,
		"Sprite list", make_rect(20, 10, 25, 0));
	tmp = d->sprite_types->firstelement;
	x = 10;
	y = 50;
	while (tmp)
	{
		render_sprite_apply(d, tmp, x, y);
		x += 180;
		if (x + 180 >= d->editor.bsr_rect.w)
		{
			x = 10;
			y += 80;
		}
		tmp = tmp->next;
	}
}
