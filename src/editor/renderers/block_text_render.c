/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_text_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:52:11 by lde-batz          #+#    #+#             */
/*   Updated: 2019/05/07 21:21:35 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "editor.h"

void	render_block_apply(t_doom *doom, t_list *tmp, int x, int y)
{
	t_block_type	*tmp_bt;

	tmp_bt = (t_block_type *)tmp->content;
	draw_rect_u(doom->editor.bsr, make_rect(x, y, 170, 70),
		tmp_bt->block_color, 1);
	doom->tmp_color = make_rgb(0, 0, 0, 255);
	instant_text(doom, doom->editor.bsr,
		tmp_bt->block_name, make_rect(x + 10, y + 22, 20, 0));
	if (is_left_clicking() && mouse_in(doom->m_x, doom->m_y,
			make_rect(doom->editor.bsr_rect.x
				+ x, doom->editor.bsr_rect.y + y, 170, 70)))
		select_block_type(doom, tmp_bt);
}

void	render_blocks(t_doom *doom)
{
	t_list			*tmp;
	int				x;
	int				y;

	doom->tmp_color = make_rgb(255, 255, 255, 255);
	instant_text(doom, doom->editor.bsr,
		"Block list", make_rect(20, 10, 25, 0));
	tmp = doom->block_types->firstelement;
	x = 10;
	y = 50;
	while (tmp)
	{
		render_block_apply(doom, tmp, x, y);
		x += 180;
		if (x + 180 >= doom->editor.bsr_rect.w)
		{
			x = 10;
			y += 80;
		}
		tmp = tmp->next;
	}
}

void	render_textures_apply(t_doom *doom, t_list *tmp, int x, int y)
{
	draw_rect_u(doom->editor.bsr, make_rect(x, y, 150, 25),
		0xFF86f4ad, 1);
	doom->tmp_color = make_rgb(0, 0, 0, 255);
	instant_text(doom, doom->editor.bsr,
		tmp->content, make_rect(x + 5, y + 2, 16, 0));
	if (is_right_clicking() && mouse_in(doom->m_x, doom->m_y,
			make_rect(doom->editor.bsr_rect.x
				+ x, doom->editor.bsr_rect.y + y, 150, 25)))
		apply_block_texture(doom, add_texture(doom, tmp->content));
}

void	render_textures(t_doom *doom, int start_y)
{
	t_list			*tmp;
	int				x;
	int				y;

	x = 10;
	y = start_y;
	doom->tmp_color = make_rgb(255, 255, 255, 255);
	instant_text(doom, doom->editor.bsr,
		"Texture folder", make_rect(20, y, 18, 0));
	tmp = doom->editor.l_textures->firstelement;
	y += 27;
	while (tmp)
	{
		render_textures_apply(doom, tmp, x, y);
		x += 155;
		if (x + 155 >= doom->editor.bsr_rect.w)
		{
			x = 10;
			y += 30;
		}
		tmp = tmp->next;
	}
}
