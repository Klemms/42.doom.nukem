/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 03:39:41 by cababou           #+#    #+#             */
/*   Updated: 2019/05/06 07:26:55 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
		while (i < tmp_texture->tex_pixels)
		{
			write_intdl(fd, ((Uint32 *)tmp_texture->surface->pixels)[i],
				i < tmp_texture->tex_pixels - 1, 0);
			i++;
		}
		ft_putendl_fd("]", fd);
		tmp = tmp->next;
	}
}
