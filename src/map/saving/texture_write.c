/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 03:39:41 by cababou           #+#    #+#             */
/*   Updated: 2019/05/07 20:52:37 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	wrt_sprite(t_sprite *s, int fd)
{
	write_intdl(fd, s->texture, 1, 0);
	write_intdl(fd, s->texture_back, 1, 0);
	write_intdl(fd, s->render_mode, 1, 0);
	write_intdl(fd, s->base_x, 1, 0);
	write_intdl(fd, s->base_y, 1, 0);
	write_intdl(fd, s->collides, 1, 0);
	write_intdl(fd, s->type, 1, 0);
	write_intdl(fd, s->obtainable, 1, 0);
	write_intdl(fd, -1, 1, 0);
	write_intdl(fd, -1, 0, 0);
}

void	wrt_sprites(t_nmap *m, int fd)
{
	t_list		*tmp;
	t_sprite	*tmp_sprite;

	tmp = m->sprites->firstelement;
	write_intdl(fd, spritecount(m->sprites->firstelement), 0, 1);
	while (tmp)
	{
		tmp_sprite = tmp->content;
		if (!tmp_sprite->dontsave)
		{
			ft_putchar_fd('[', fd);
			wrt_sprite(tmp_sprite, fd);
			ft_putendl_fd("]", fd);
		}
		tmp = tmp->next;
	}
}

void	wrt_textures(t_nmap *m, int fd)
{
	t_list		*tmp;
	t_texture	*tmp_texture;
	int			sz;
	size_t		i;

	tmp = m->textures->firstelement;
	sz = lstcontainer_size(m->textures);
	write_intdl(fd, sz, 0, 1);
	while (tmp)
	{
		i = 0;
		tmp_texture = (t_texture *)tmp->content;
		ft_putchar_fd('[', fd);
		write_intdl(fd, tmp_texture->surface->w, 1, 0);
		write_intdl(fd, tmp_texture->surface->h, 1, 0);
		while (i < (size_t)tmp_texture->tex_pixels)
		{
			write_intdl(fd, ((Uint32 *)tmp_texture->surface->pixels)[i],
				i < (size_t)tmp_texture->tex_pixels - 1, 0);
			i++;
		}
		ft_putendl_fd("]", fd);
		tmp = tmp->next;
	}
}
