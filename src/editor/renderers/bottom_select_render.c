/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bottom_select_render.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:52:11 by lde-batz          #+#    #+#             */
/*   Updated: 2019/05/07 21:18:00 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "editor.h"

void	render_ext_apply(t_doom *doom, t_list *tmp, int x, int y)
{
	t_texture		*tmp_text;
	SDL_Rect		dest;

	dest = make_rect(x, y, 50, 50);
	tmp_text = (t_texture *)tmp->content;
	SDL_BlitScaled(tmp_text->surface, NULL, doom->editor.bsr, &dest);
	if (is_right_clicking() && mouse_in(doom->m_x, doom->m_y,
			make_rect(doom->editor.bsr_rect.x
				+ x, doom->editor.bsr_rect.y + y, 50, 50)))
		apply_block_texture(doom, tmp->index);
}

int		render_existing_textures(t_doom *doom)
{
	t_list			*tmp;
	int				x;
	int				y;

	doom->tmp_color = make_rgb(255, 255, 255, 255);
	instant_text(doom, doom->editor.bsr,
		"Existing textures", make_rect(20, 7, 18, 0));
	tmp = doom->nmap->textures->firstelement;
	x = 10;
	y = 35;
	while (tmp)
	{
		render_ext_apply(doom, tmp, x, y);
		x += 55;
		if (x + 55 >= doom->editor.bsr_rect.w)
		{
			x = 10;
			y += 55;
		}
		tmp = tmp->next;
	}
	return (y + 55);
}

void	editor_bsr_brender(t_doom *doom)
{
	t_editor	*e;

	e = &doom->editor;
	draw_rect_u(e->bsr, make_rect(0, 0,
			e->bsr_rect.w, e->bsr_rect.h),
		0xFF626468, 1);
	editor_bsr_mrender(doom);
	draw_rect_u(e->bsr, make_rect(0, 0,
			e->bsr_rect.w, e->bsr_rect.h),
		0xFF000000, 0);
	SDL_BlitSurface(e->bsr, NULL, doom->editor.ed_surface,
		&e->bsr_rect);
}

void	editor_bsr_mrender(t_doom *doom)
{
	if (doom->editor.hand_tool == tool_block)
	{
		render_blocks(doom);
	}
	else if (doom->editor.hand_tool == tool_textures)
	{
		render_textures(doom, render_existing_textures(doom));
	}
	else if (doom->editor.hand_tool == tool_sprite)
	{
		render_sprites(doom);
	}
}
